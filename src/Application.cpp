#include "Application.hpp"

const String Application::DATA_FOLDER = "data/";
const String Application::USER_FILE = DATA_FOLDER + "userlist.dat";
const String Application::CLIENT_FILE = DATA_FOLDER + "clients.dat";
const String Application::OPTION_FILE = DATA_FOLDER + "Options.csv";
const String Application::MODEL_FILE = DATA_FOLDER + "Modeles.csv";
const String Application::CONTRACT_FILE = DATA_FOLDER + "contracts.dat";

void Application::loadUsers() {
    ifstream is(USER_FILE, ios::in);
    Sanity::streamness(is, "Failed to open " + USER_FILE);

    this->userId = StreamUtils::read<unsigned int>(is);
    this->users.addAll(StreamUtils::readSortedList<Employee>(is));
}

void Application::defaultUsers() {
    Employee e("Placeholder", "Administrateur", ++this->userId, "admin", Employee::ADMINISTRATIVE);
    e.setPassword("admin000");
    this->users.add(e);
}

void Application::saveUsers() const {
    ofstream os(USER_FILE, ios::out | ios::trunc);
    Sanity::streamness(os, "Failed to open " + USER_FILE);

    StreamUtils::write(os, this->userId);
    StreamUtils::writeList<Employee>(os, this->users);
}

void Application::loadClients() {
    ifstream is(CLIENT_FILE, ios::in);
    Sanity::streamness(is, "Failed to open " + CLIENT_FILE);

    this->clientId = StreamUtils::read<unsigned int>(is);
    this->clients.addAll(StreamUtils::readSortedList<Client>(is));
}

void Application::saveClients() const {
    ofstream os(CLIENT_FILE, ios::out | ios::trunc);
    Sanity::streamness(os, "Failed to open " + CLIENT_FILE);

    StreamUtils::write(os, this->clientId);
    StreamUtils::writeList<Client>(os, this->clients);
}

void Application::loadContracts() {
    ifstream is(CONTRACT_FILE, ios::in);
    Sanity::streamness(is, "Failed to open " + CONTRACT_FILE);

    this->contractId = StreamUtils::read<unsigned int>(is);
    this->contracts.addAll(StreamUtils::readSortedList<Contract>(is));
}

void Application::saveContracts() const {
    ofstream os(CONTRACT_FILE, ios::out | ios::trunc);
    Sanity::streamness(os, "Failed to open " + CONTRACT_FILE);

    StreamUtils::write(os, this->contractId);
    StreamUtils::writeList<Contract>(os, this->contracts);
}

void Application::loadModels() {
    ifstream is(MODEL_FILE, ios::in);
    Sanity::streamness(is, "Failed to open " + MODEL_FILE);

    List<String> l;

    cerr << time("Application") << "Loading models from " << MODEL_FILE << endl;
    StreamUtils::skipLine(is); // Validate file format?
    int i = 0;
    while(is.peek() != EOF) {
        // Reading data
        l = StreamUtils::readCSVLine(is, 4);
        ConstIterator<String> it(l);
        String name(it++.get());
        int power = it++.get().toInt();
        bool diesel = it++.get().toBool();
        float baseCost = it.get().toFloat();

        // Adding to list
        this->models.add(Model(name, power, diesel, baseCost));

        // Adding to table
        String line[] = {
            String::valueOf(i++),
            name,
            String::valueOf(baseCost),
            String::valueOf(power),
            diesel ? "yes" : "no"
        };
        this->modelTable.addLine(line);
    }
    cerr << time("Application") << this->models.size() << " models loaded" << endl;
}

void Application::loadOptions() {
    ifstream is(OPTION_FILE, ios::in);
    Sanity::streamness(is, "Failed to open " + OPTION_FILE);

    List<String> l;

    cerr << time("Application") << "Loading options from " << OPTION_FILE << endl;
    StreamUtils::skipLine(is); // Validate file format?
    while(is.peek() != EOF) {
        l = StreamUtils::readCSVLine(is, 3);
        ConstIterator<String> it(l);
        String code = it++;
        String name = it++;
        float price = it.get().toFloat();

        // Adding to list
        this->options.add(Option(code, name, price));

        // Adding to table
        String line[] = {
            code,
            name,
            String::valueOf(price)
        };
        this->optionTable.addLine(line);
    }
    cerr << time("Application") << this->options.size() << " options loaded" << endl;
}

Application::Application() : optionTable(3), modelTable(5) {
    String optionHeaders[] = { "code", "name", "price" };
    this->optionTable.setHeader(optionHeaders);

    String modelHeaders[] = { "id", "name", "base cost", "power", "diesel" };
    this->modelTable.setHeader(modelHeaders);

    this->currentCar = NULL;
    this->carDirty = false;
    this->quitFlag = false;
    this->loaded = false;
    this->userId = 0;
    this->clientId = 0;
    this->contractId = 0;
}

Application::~Application() {
    if(this->currentCar) {
        delete this->currentCar;
    }
}

void Application::load() {
    Sanity::truthness(!this->loaded, "Application already loaded");

    if(FileUtils::exists(USER_FILE)) {
        cerr << time("Application::load") << "Loading users" << endl;
        this->loadUsers();
    } else {
        cerr << time("Application::load") << "Default user" << endl;
        this->defaultUsers();
    }
    if(FileUtils::exists(CLIENT_FILE)) {
        cerr << time("Application::load") << "Loading clients" << endl;
        this->loadClients();
    }
    if(FileUtils::exists(CONTRACT_FILE)) {
        cerr << time("Application::load") << "Loading contracts" << endl;
        this->loadContracts();
    }

    cerr << time("Application::load") << "Loading models" << endl;
    this->loadModels();
    cerr << time("Application::load") << "Loading options" << endl;
    this->loadOptions();

    this->loaded = true;
}

void Application::save() {
    cerr << time("Application::save") << "Saving users" << endl;
    this->saveUsers();
    cerr << time("Application::save") << "Saving clients" << endl;
    this->saveClients();
    cerr << time("Application::save") << "Saving contracts" << endl;
    this->saveContracts();
    if(this->currentCar && this->carDirty) {
        String input;
        cout << " Current car is dirty, would you like to save it? ";
        cin >> input;
        if(input.toBool()) {
            cerr << time("Application::save") << "Saving dirty car" << endl;
            this->saveCurrentCar();
        }
    }
}

bool Application::login(const String& providedLogin, const String& providedPassword) {
    if(this->authenticator.quickLogin(providedLogin, providedPassword, this->users)) {
        return true;
    }

    return this->authenticator.login(this->users);
}

Employee& Application::getCurrentUser() {
    return this->authenticator.getCurrentUser();
}

bool Application::shouldQuit() const {
    return this->quitFlag;
}

void Application::changePassword() {
    this->authenticator.changePassword();
}

void Application::quit() {
    this->quitFlag = true;
}

void Application::displayUsers() {
    if(this->users.isEmpty()) {
        cout << " > No users" << endl;
        return;
    }

    Table table(6);
    String headers[] = { "id", "login", "firstname", "surname", "function", "password" };
    table.setHeader(headers);
    ConstIterator<Employee> it(this->users);
    while(!it.end()) {
        String line[] = {
            String::valueOf(it.get().getId()),
            String(it.get().getLogin()),
            String(it.get().getFirstname()),
            String(it.get().getSurname()),
            String(it.get().getFunction()),
            it.get().getPassword().isEmpty() ? "<empty>" : String('*', it.get().getPassword().length())
        };
        table.addLine(line);
        ++it;
    }
    cout << table.toString() << endl;
}

void Application::displayUser() {
    String username;
    cout << "    Enter the login of the user you're looking for: ";
    cin >> username;
    if(username.isEmpty()) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = this->users.getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        cout << endl << EmployeeFormatter(opt.get()).format(4) << endl;
    } else {
        cout << " > User not found :(" << endl;
    }
}

void Application::createUser() {
    String surname, firstname, login, func;
    bool bFunc;

    cout << endl << "    = Creating new user =" << endl;
    cout << "    User login: ";
    cin >> login;
    cout << "    User firstname: ";
    cin >> firstname;
    cout << "    User surname: ";
    cin >> surname;
    cout << "    Function (is " << Employee::ADMINISTRATIVE << "?): ";
    cin >> func;
    bFunc = func.toBool();

    if(this->users.containsWithPredicate(LoginPredicate(login))) {
        cout << " > There is already a user with the username " << login << endl;
        return;
    }

    this->users.add(Employee(surname, firstname, ++this->userId, login, bFunc ? Employee::ADMINISTRATIVE : Employee::SELLER));
    cout << " > User " << green << login << reset << " successfuly created" << endl;
}

void Application::resetPassword() {
    this->authenticator.resetPassword(this->users);
}

void Application::displayContracts() {
    if(this->contracts.isEmpty()) {
        cout << " > No contracts" << endl;
        return;
    }

    Table table(6);
    String headers[] = { "id", "seller id", "client id", "date", "car", "discount" };
    table.setHeader(headers);
    ConstIterator<Contract> it(this->contracts);
    while(!it.end()) {
        String line[] = {
            String::valueOf(it.get().getId()),
            String::valueOf(it.get().getSellerId()),
            String::valueOf(it.get().getClientId()),
            it.get().getDate().format("%d-%m-%y"),
            it.get().getCar().getName(),
            String::valueOf(it.get().getDiscount())
        };
        table.addLine(line);
        ++it;
    }
    cout << table.toString() << endl;
}

void Application::displayContract() {
    String input;
    unsigned int id;
    cout << "    Enter the id of the contract: ";
    cin >> input;
    try {
        id = input.toUnsignedInt();
    } catch(invalid_argument e) {
        cout << " > Not a valid integer" << endl;
        return;
    }

    Optional<Contract> opt = this->contracts.getFirstMatching(IdPredicate<Contract>(id));
    if(opt.hasValue()) {
        cout << endl << ContractFormatter(opt.get()).format(4) << endl;
    } else {
        cout << " > id not found" << endl;
    }
}

void Application::displaySellerContracts() {
    String name;
    cout << "    Enter the seller login: "; // Should be firstname (as per teacher's instructions)
    cin >> name;

    // Should use FirstnamePredicate, but firstname isn't unique, maybe we should list them all?
    Optional<Employee> optEmployee = this->users.getFirstMatching(LoginPredicate(name));
    if(!optEmployee.hasValue()) {
        cout << " > There is no seller with this name" << endl;
        return;
    }
    if(optEmployee.get().getFunction() == Employee::ADMINISTRATIVE) {
        cout << " > This employee is not a seller" << endl;
        return;
    }
    unsigned int sellerId = optEmployee.get().getId();

    bool stuffWasDisplayed = false;
    float sales = 0;
    ConstIterator<Contract> contractIt(this->contracts);
    while(!contractIt.end()) {
        if(contractIt.get().getSellerId() == sellerId) {
            cout << endl << ContractFormatter(contractIt).format(4) << endl;
            stuffWasDisplayed = true;
            sales += contractIt.get().getCar().getPrice() - contractIt.get().getDiscount();
        }
        ++contractIt;
    }

    if(stuffWasDisplayed) {
        cout << endl << "    Total sales: " << sales << " EUR" << endl;
    } else {
        cout << " > No contracts for this seller" << endl;
    }
}

void Application::createClient() {
    String address, firstname, surname;
    cout << endl << "    = Creating new client =" << endl;
    cout << "    Enter client address: ";
    cin >> address;
    cout << "    Enter client firstname: ";
    cin >> firstname;
    cout << "    Enter client surname: ";
    cin >> surname;

    this->clients.add(Client(surname, firstname, ++this->clientId, address));
    cout << " > Client " << green << firstname << ' ' << surname << reset << " created." << endl;
}

void Application::removeClient() {
    String input;
    unsigned int id;
    cout << "    Enter the id of the client to remove: ";
    cin >> input;
    try {
        id = input.toUnsignedInt();
    } catch(invalid_argument e) {
        cout << " > " << e.what() << endl;
        return;
    }

    if(this->contracts.containsWithPredicate(ClientIdPredicate(id))) {
        cout << " > Client is involved in a contract and can't be removed" << endl;
        return;
    }

    Iterator<Client> clientIt(this->clients);
    while(!clientIt.end()) {
        if(clientIt.get().getId() == id) {
            clientIt.remove();
            cout << " > Client removed" << endl;
            return;
        }
        ++clientIt;
    }
    cout << " > Client not found" << endl;
}

void Application::displayClients() {
    if(this->clients.isEmpty()) {
        cout << " > No clients" << endl;
        return;
    }

    Table table(4);
    String headers[] = { "id", "address", "firstname", "surname" };
    table.setHeader(headers);
    ConstIterator<Client> it(this->clients);
    while(!it.end()) {
        String line[] = {
            String::valueOf(it.get().getId()),
            String(it.get().getAddress()),
            String(it.get().getFirstname()),
            String(it.get().getSurname())
        };
        table.addLine(line);
        ++it;
    }
    cout << table.toString() << endl;
}

void Application::displayModels() {
    if(this->models.isEmpty()) {
        cout << " > No models yet" << endl;
        return;
    }

    cout << this->modelTable.toString() << endl;
}

void Application::displayOptions() {
    if(this->options.isEmpty()) {
        cout << " > No options yet" << endl;
        return;
    }

    cout << this->optionTable.toString() << endl;
}

void Application::createCar() {
    if(this->currentCar) {
        if(this->carDirty) {
            String input;
            cout << "    There was changes to the current car, would you like to save them? ";
            cin >> input;
            if(input.toBool()) {
                this->saveCurrentCar();
            }
        }
        delete this->currentCar;
        this->currentCar = NULL;
    }

    String carName;
    String modelInput;
    unsigned int modelId;

    cout << "    Enter the car project name: ";
    cin >> carName;

    while(true) {
        cout << "    Enter the model id: ";
        cin >> modelInput;
        try {
            modelId = modelInput.toUnsignedInt();
        } catch(invalid_argument e) {
            cout << " > " << e.what() << endl;
            continue;
        }
        break;
    }

    if(modelId >= this->models.size()) {
        cout << " > Model not found";
        return;
    }

    this->currentCar = new Car(carName, this->models.get(modelId));
    this->carDirty = true;
    cout << " > Car created and loaded" << endl;
}

void Application::loadCar() {
    if(this->currentCar) {
        if(this->carDirty) {
            String input;
            cout << "    There was changes to the current car, would you like to save them? ";
            cin >> input;
            if(input.toBool()) {
                this->saveCurrentCar();
            }
        }
    } else {
        this->currentCar = new Car();
    }
    this->carDirty = false;

    String input;
    cout << "    Enter the name of the project to load: ";
    cin >> input;
    try {
        this->currentCar->load(DATA_FOLDER + input + ".car");
    } catch(AssertionException e) {
        cout << " > " << e.what() << endl;
        delete this->currentCar;
        this->currentCar = NULL;
        return;
    }
    cout << " > Car loaded" << endl;
}

void Application::displayCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }

    cout << CarFormatter(*this->currentCar).format(4) << endl;
}

void Application::addOptionToCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }

    String input;
    cout << "    Enter the code of the option to add: ";
    cin >> input;

    Optional<Option> opt = this->options.getFirstMatching(CodePredicate(input));
    if(opt.hasValue()) {
        try {
            this->currentCar->addOption(opt.get());
        } catch(NotEnoughSpaceException e) {
            cout << " > Too much options on this car" << endl;
            return;
        } catch(AssertionException e) {
            cout << " > This car already has this option" << endl;
            return;
        }

        this->carDirty = true;
        cout << " > Option added to the current car" << endl;
        return;
    } else {
        cout << " > Option not found" << endl;
    }
}

void Application::removeOptionFromCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }

    String input;
    cout << "    Enter the code of the option to remove: ";
    cin >> input;

    try {
        this->currentCar->removeOption(input);
    } catch(ElementNotFoundException e) {
        cout << " > Current car doesn't have this option" << endl;
        return;
    }
    cout << " > Option removed from the current car" << endl;
    this->carDirty = true;
}

void Application::applyDiscountToCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }

    String input;
    cout << "    Enter the code of the option: ";
    cin >> input;

    try {
        Option& option = this->currentCar->getOption(input);
        if(option.getPrice() == 0) {
            cout << " > Option is already free, we ain't going lower..." << endl;
            return;
        }
        --option;
    } catch(ElementNotFoundException e) {
        cout << " > The car doesn't have this option" << endl;
        return;
    }
    cout << " > Discount applied" << endl;
    this->carDirty = true;
}

void Application::saveCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car to save" << endl;
        return;
    }
    this->currentCar->save();
    Optional<Contract> opt = this->contracts.getFirstMatching(NamePredicate(this->currentCar->getName()));
    if(opt.hasValue()) {
        opt.get().setCar(*this->currentCar);
    }
    cout << " > Car saved" << endl;
    this->carDirty = false;
}

void Application::newContract() {
    String carName, input;
    unsigned int clientId;

    while(true) {
        cout << "    Enter the client id: ";
        cin >> input;
        try {
            clientId = input.toUnsignedInt();
        } catch(invalid_argument e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }
    if(!this->clients.containsWithPredicate(IdPredicate<Client>(clientId))) {
        cout << " > Unknown client id" << endl;
        return;
    }

    cout << "    Enter the name of the car project: ";
    cin >> carName;

    Car car;
    if(this->currentCar && this->currentCar->getName() == carName) {
        car = *this->currentCar;
        // If the car was never saved before, the contract could be linked to a non existing car
        this->currentCar->save();
    } else {
        try {
            car.load(DATA_FOLDER + carName + ".car");
        } catch(AssertionException e) {
            cout << e.what() << endl;
            return;
        }
    }

    this->contracts.add(Contract(++this->contractId, this->getCurrentUser().getId(), clientId, Date(), car));
    cout << " > Contract added" << endl;
}

void Application::displayContractsForCurrentUser() {
    bool displayedStuff = false;

    Table table(6);
    String headers[] = { "id", "seller id", "client id", "date", "car", "discount" };
    table.setHeader(headers);
    ConstIterator<Contract> it(this->contracts);
    while(!it.end()) {
        if(it.get().getSellerId() == this->getCurrentUser().getId()) {
            String line[] = {
                String::valueOf(it.get().getId()),
                String::valueOf(it.get().getSellerId()),
                String::valueOf(it.get().getClientId()),
                it.get().getDate().format("%d-%m-%y"),
                it.get().getCar().getName(),
                String::valueOf(it.get().getDiscount())
            };
            table.addLine(line);
            displayedStuff = true;
        }
        ++it;
    }
    if(displayedStuff) {
        cout << table.toString() << endl;
    } else {
        cout << " > No contract made by the current user" << endl;
    }
}

void Application::modifyContract() {
    String input;
    unsigned int id;

    while(true) {
        cout << "    Enter the id of the contract you want to modify: ";
        cin >> input;
        try {
            id = input.toUnsignedInt();
        } catch(invalid_argument e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    Optional<Contract> opt = this->contracts.getFirstMatching(IdPredicate<Contract>(id));
    if(!opt.hasValue()) {
        cout << " > Contract not found" << endl;
        return;
    }

    unsigned int choice;
    while(true) {
        cout
            << endl
            << "    What do you want to modify?" << endl
            << "    0. I'm done with this" << endl
            << "    1. Contract discount" << endl
            << "    2. Car project" << endl << endl
            << "    Your choice: ";
        cin >> input;

        try {
            choice = input.toUnsignedInt();
        } catch(invalid_argument e) {
            cout << " > Invalid choice" << endl;
            continue;
        }

        switch(choice) {
            case 0:
                return;
            case 1:
                cout << "    Enter the new discount: ";
                cin >> input;
                float discount;
                try {
                    discount = input.toFloat();
                } catch(invalid_argument e) {
                    cout << " > " << e.what() << endl;
                    continue;
                }
                if(discount >= opt.get().getCar().getModel().getBaseCost()) {
                    cout << " > Discount is greater than the car price, we're not paying you to get a car ._." << endl;
                    continue;
                }
                opt.get().setDiscount(discount);
                cout << " > new discount set" << endl;
                break;
            case 2:
                cout << "    Enter the name of the new car project: ";
                cin >> input;
                if(this->currentCar && this->currentCar->getName() == input) {
                    opt.get().setCar(*this->currentCar);
                } else {
                    try {
                        opt.get().getCar().load(DATA_FOLDER + input + ".car");
                    } catch(AssertionException e) {
                        cout << " > " << e.what() << endl;
                        continue;
                    }
                }
                cout << " > new car set" << endl;
                break;
            default:
                cout << " > Invalid choice" << endl;
        }
    }
}
