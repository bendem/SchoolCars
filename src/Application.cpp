#include "Application.hpp"

Application::Application() : optionTable(3), modelTable(5) {
    String optionHeaders[] = { "code", "name", "price" };
    this->optionTable.setHeader(optionHeaders);

    String modelHeaders[] = { "id", "name", "base cost", "power", "diesel" };
    this->modelTable.setHeader(modelHeaders);

    this->currentUser = NULL;
    this->currentCar = NULL;
    this->carDirty = false;
    this->quitFlag = false;
    this->userId = 0;
    this->clientId = 0;
    this->contractId = 0;
}

Application::~Application() {
    // Not removing this->currentUser as it points directly inside this->users and will be deleted with the list
    if(this->currentCar) {
        delete this->currentCar;
    }
}

void Application::loadUsers(const String& userfile) {
    Sanity::truthness(this->users.isEmpty(), "Users were already loaded");

    ifstream is(userfile, ios::in);
    int count = StreamUtils::readInt(is);
    this->userId = StreamUtils::readInt(is);

    Employee e;
    for(int i = 0; i < count; ++i) {
        e.load(is);
        this->users.add(e);
    }
}

void Application::defaultUsers() {
    Sanity::truthness(this->users.isEmpty(), "Can't create default users, some already exist");

    Employee e("Placeholder", "Administrateur", ++this->userId, "admin", Employee::ADMINISTRATIVE);
    e.setPassword("admin000");
    this->users.add(e);
}

void Application::saveUsers(const String& file) const {
    ofstream os(file, ios::out | ios::trunc);
    if(os.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    StreamUtils::write(os, this->users.size());
    StreamUtils::write(os, this->userId);

    ConstIterator<Employee> it(this->users);
    while(!it.end()) {
        ((Employee) it++).save(os);
    }
}

void Application::loadClients(const String& file) {
    ifstream is(file, ios::in);
    if(is.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    int count = StreamUtils::readInt(is);
    this->clientId = StreamUtils::readInt(is);

    Client c;
    for(int i = 0; i < count; ++i) {
        c.load(is);
        this->clients.add(c);
    }
}

void Application::saveClients(const String& file) const {
    ofstream os(file, ios::out | ios::trunc);
    if(os.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    StreamUtils::write(os, this->clients.size());
    StreamUtils::write(os, this->clientId);

    ConstIterator<Client> it(this->clients);
    while(!it.end()) {
        ((Client) it++).save(os);
    }
}

void Application::loadContracts(const String& file) {
    ifstream is(file, ios::in);
    if(is.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    int count = StreamUtils::readInt(is);
    this->contractId = StreamUtils::readInt(is);

    Contract c;
    for(int i = 0; i < count; ++i) {
        c.load(is);
        this->contracts.add(c);
    }
}

void Application::saveContracts(const String& file) const {
    ofstream os(file, ios::out | ios::trunc);
    if(os.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    StreamUtils::write(os, this->contracts.size());
    StreamUtils::write(os, this->contractId);

    ConstIterator<Contract> it(this->contracts);
    while(!it.end()) {
        ((Contract) it++).save(os);
    }
}

void Application::loadModels(const String& file) {
    Sanity::truthness(this->models.isEmpty(), "Models are already loaded");

    ifstream is(file, ios::in);
    if(is.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    List<String> l;

    cerr << time("Application") << "Loading models from " << file << endl;
    StreamUtils::skipLine(is); // Validate file format?
    int i = 0;
    while(is.peek() != EOF) {
        // Reading data
        l = StreamUtils::readCSVLine(is, 4);
        ConstIterator<String> it(l);
        String name(&it++);
        int power = (&it++).toInt();
        bool diesel = (&it++).toBool();
        float baseCost = (&it).toFloat();

        // Adding to list
        this->models.add(Model(name, power, diesel, baseCost));

        // Adding to table
        String line[] = {
            String() + i++,
            name,
            String() + baseCost,
            String() + power,
            String(diesel ? "yes" : "no")
        };
        this->modelTable.addLine(line);
    }
    cerr << time("Application") << this->models.size() << " models loaded" << endl;
}

void Application::loadOptions(const String& file) {
    Sanity::truthness(this->models.isEmpty(), "Options are already loaded");

    ifstream is(file, ios::in);
    if(is.fail()) {
        throw IOException(String("Couldn't open ") + file);
    }

    List<String> l;

    cerr << time("Application") << "Loading options from " << file << endl;
    StreamUtils::skipLine(is); // Validate file format?
    while(is.peek() != EOF) {
        l = StreamUtils::readCSVLine(is, 3);
        ConstIterator<String> it(l);
        String code = it++;
        String name = it++;
        float price = (&it).toFloat();

        // Adding to list
        this->options.add(Option(code, name, price));

        // Adding to table
        String line[] = {
            code,
            name,
            String() + price
        };
        this->optionTable.addLine(line);
    }
    cerr << time("Application") << this->options.size() << " options loaded" << endl;
}


bool Application::login(const String& providedLogin, const String& providedPassword) {
    if(providedLogin.length() != 0 && providedPassword.length() != 0) {
        // Quick arg login
        Optional<Employee> opt = this->users.getFirstMatching(LoginPredicate(providedLogin));
        if(opt.hasValue() && opt.get().getPassword() == providedPassword) {
            this->currentUser = &opt.get();
            return true;
        }
    }

    String username, password;

    cout << "    ========================" << endl;
    cout << "    =        Login         =" << endl;
    cout << "    ========================" << endl << endl;
    cout << "    Entrez votre nom d'utilisateur: ";
    cin >> username;
    cout << endl;

    Optional<Employee> optEmployee = this->users.getFirstMatching(LoginPredicate(username));
    if(!optEmployee.hasValue()) {
        cout << " > User not found" << endl;
        return false;
    }

    // Password not set
    if(optEmployee.get().getPassword().length() == 0) {
        cerr << time("Application") << "Found user without password, logging in and asking password" << endl;
        this->currentUser = &optEmployee.get();
        String newPassword;
        String confirmation;
        while(true) {
            cout << endl << "    404 password not found, enter a new one: ";
            cin >> newPassword;
            cout << "    Confirm your password: ";
            cin >> confirmation;
            if(newPassword != confirmation) {
                cout << " > Passwords don't match, try again" << endl;
                continue;
            }
            try {
                this->currentUser->setPassword(newPassword);
            } catch(InvalidPasswordException e) {
                cout << " > " << e.what() << ", try again" << endl;
                continue;
            }
            break;
        }
        return true;
    }

    cout << "    Entrez votre mot de passe: ";
    cin >> password;

    // Correct password
    if(optEmployee.get().getPassword() == password) {
        cerr << time("Application") << "Found correct user, logging in" << endl;
        this->currentUser = &optEmployee.get();
        return true;
    }

    cerr << time("Application") << "Found user (" << optEmployee.get().getLogin() << ") with wrong password" << endl;
    return false;
}

Employee& Application::getCurrentUser() const {
    return *this->currentUser;
}

bool Application::shouldQuit() const {
    return this->quitFlag;
}

void Application::changePassword() {
    String current, newPassword, confirmation;

    cout << "    Type your current password: ";
    cin >> current;
    if(this->currentUser->getPassword() != current) {
        cout << " > Incorrect password" << endl;
        return;
    }

    cout << "    Type your new password: ";
    cin >> newPassword;
    cout << "    Confirm your password: ";
    cin >> confirmation;

    if(newPassword != confirmation) {
        cout << " > Passwords do not match!" << endl;
        return;
    }

    try {
        this->currentUser->setPassword(newPassword);
    } catch(InvalidPasswordException e) {
        cout << e.what() << endl;
        return;
    }
    cout << " > Password changed" << endl;
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
            String() + (&it).getId(),
            String((&it).getLogin()),
            String((&it).getFirstname()),
            String((&it).getSurname()),
            String((&it).getFunction()),
            (&it).getPassword().length() == 0 ? "<empty>" : String('*', (&it).getPassword().length())
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
    if(username.length() == 0) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = this->users.getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        cout << endl << "    = " << username << " =" << endl
            << "    Id: \t" << opt.get().getId() << endl
            << "    Login: \t" << opt.get().getLogin() << endl
            << "    Password: \t" << (opt.get().getPassword().length() == 0 ? "<empty>" : String('*', opt.get().getPassword().length())) << endl
            << "    Function: \t" << opt.get().getFunction() << endl
            << "    Firstname: \t" << opt.get().getFirstname() << endl
            << "    Surname: \t" << opt.get().getSurname() << endl;
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
    cout << " > User successfuly created" << endl;
}

void Application::resetPassword() {
    String username;
    cout << "    Enter the login of the user you want to reset the pwd for: ";
    cin >> username;
    if(username.length() == 0) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = this->users.getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        opt.get().resetPassword();
        cout << " > " << username << "'s password has been reset" << username << endl;
    } else {
        cout << " > User not found :(" << endl;
    }
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
            String() + (&it).getId(),
            String() + (&it).getSellerId(),
            String() + (&it).getClientId(),
            (&it).getDate().format("%d-%m-%y"),
            (&it).getCar().getName(),
            String() + (&it).getDiscount()
        };
        table.addLine(line);
        ++it;
    }
    cout << table.toString() << endl;
}

void Application::displayContract() {
    String input;
    int id;
    cout << "    Enter the id of the contract: ";
    cin >> input;
    try {
        id = input.toInt();
    } catch(invalid_argument e) {
        cout << " > Not a valid integer" << endl;
        return;
    }

    Optional<Contract> opt = this->contracts.getFirstMatching(IdPredicate<Contract>(id));
    if(opt.hasValue()) {
        cout << ContractFormatter(opt.get()).format(4) << endl;
    } else {
        cout << " > id not found" << endl;
    }
}

void Application::displaySellerContracts() {
    String input;
    int id;
    cout << "    Enter the seller id: ";
    cin >> input;
    try {
        id = input.toInt();
    } catch(invalid_argument e) {
        cout << " > " << e.what() << endl;
        return;
    }

    Optional<Employee> optEmployee = this->users.getFirstMatching(IdPredicate<Employee>(id));
    if(!optEmployee.hasValue()) {
        cout << " > There is no seller with this id" << endl;
        return;
    }
    if(optEmployee.get().getFunction() == Employee::ADMINISTRATIVE) {
        cout << " > This employee is not a seller" << endl;
        return;
    }

    bool stuffWasDisplayed = false;
    ConstIterator<Contract> contractIt(this->contracts);
    while(!contractIt.end()) {
        if((&contractIt).getSellerId() == id) {
            cout << ContractFormatter(contractIt).format(4) << endl;
            stuffWasDisplayed = true;
        }
        ++contractIt;
    }

    if(!stuffWasDisplayed) {
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
}

void Application::removeClient() {
    String input;
    int id;
    cout << "    Enter the id of the client to remove: ";
    cin >> input;
    try {
        id = input.toInt();
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
        if((&clientIt).getId() == id) {
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
            String() + (&it).getId(),
            String((&it).getAddress()),
            String((&it).getFirstname()),
            String((&it).getSurname())
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
    int modelId;

    cout << "    Enter the car project name: ";
    cin >> carName;

    while(true) {
        cout << "    Enter the model id: ";
        cin >> modelInput;
        try {
            modelId = modelInput.toInt();
        } catch(invalid_argument e) {
            cout << " > " << e.what() << endl;
            continue;
        }
        break;
    }

    if(modelId < 0 || modelId >= this->models.size()) {
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
        this->currentCar->load(String("data/") + input + ".car");
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
        --this->currentCar->getOption(input);
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
    cout << " > Car saved" << endl;
    this->carDirty = false;
}

void Application::newContract() {
    String carName, input;
    int clientId;

    while(true) {
        cout << "    Enter the client id: ";
        cin >> input;
        try {
            clientId = input.toInt();
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
    } else {
        try {
            car.load(String("data/") + carName + ".car");
        } catch(AssertionException e) {
            cout << e.what() << endl;
            return;
        }
    }

    this->contracts.add(Contract(++this->contractId, this->currentUser->getId(), clientId, Date(), car));
    cout << " > Contract added" << endl;
}

void Application::displayContractsForCurrentUser() {
    bool displayedStuff = false;

    Table table(6);
    String headers[] = { "id", "seller id", "client id", "date", "car", "discount" };
    table.setHeader(headers);
    ConstIterator<Contract> it(this->contracts);
    while(!it.end()) {
        if((&it).getSellerId() == this->currentUser->getId()) {
            String line[] = {
                String() + (&it).getId(),
                String() + (&it).getSellerId(),
                String() + (&it).getClientId(),
                (&it).getDate().format("%d-%m-%y"),
                (&it).getCar().getName(),
                String() + (&it).getDiscount()
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
    int id;

    while(true) {
        cout << "    Enter the id of the contract you want to modify: ";
        cin >> input;
        try {
            id = input.toInt();
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

    int choice;
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
            choice = input.toInt();
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
                        opt.get().getCar().load(String("data/") + input + ".car");
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
