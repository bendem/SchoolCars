#include "Application.hpp"

Application::Application() {
    this->users = NULL;
    this->clients = new SortedList<Client>();
    this->options = NULL;
    this->models = NULL;
    this->contracts = new SortedList<Contract>();
    this->currentUser = NULL;
    this->currentCar = NULL;
    this->carDirty = false;
    this->quitFlag = false;
}

Application::~Application() {
    if(this->users) {
        delete this->users;
    }
    if(this->clients) {
        delete this->clients;
    }
    if(this->options) {
        delete this->options;
    }
    if(this->models) {
        delete this->models;
    }
    if(this->contracts) {
        delete this->contracts;
    }
    // Not removing this->currentUser as it points directly inside this->users and will be deleted with the list
    if(this->currentCar) {
        delete this->currentCar;
    }
}

void Application::loadUsers(const String& userfile) {
    Sanity::truthness(this->users == NULL, "Users were already loaded");

    this->users = new SortedList<Employee>();

    ifstream is(userfile, ios::in);
    int count = StreamUtils::readInt(is);

    Employee e;
    for(int i = 0; i < count; ++i) {
        e.load(is);
        this->users->add(e);
    }
}

void Application::defaultUsers() {
    Sanity::truthness(this->users == NULL, "Can't create default users, some already exist");

    this->users = new SortedList<Employee>();
    Employee e("Placeholder", "Administrateur", 0, "admin", Employee::ADMINISTRATIVE);
    e.setPassword("admin000");
    this->users->add(e);
}

void Application::saveUsers(const String& userfile) const {
    if(!this->users) {
        return;
    }
    ofstream os(userfile, ios::out | ios::trunc);
    StreamUtils::write(os, this->users->size());

    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        ((Employee) it++).save(os);
    }
}

void Application::loadClients(const String& clientfile) {
    ifstream is(clientfile, ios::in);
    int count = StreamUtils::readInt(is);

    Client c;
    for(int i = 0; i < count; ++i) {
        c.load(is);
        this->clients->add(c);
    }
}

void Application::saveClients(const String& clientfile) const {
    if(!this->clients) {
        return;
    }
    ofstream os(clientfile, ios::out | ios::trunc);
    StreamUtils::write(os, this->clients->size());

    ConstIterator<Client> it(*this->clients);
    while(!it.end()) {
        ((Client) it++).save(os);
    }
}

void Application::loadContracts(const String& file) {
    ifstream is(file, ios::in);
    int count = StreamUtils::readInt(is);

    Contract c;
    for(int i = 0; i < count; ++i) {
        c.load(is);
        this->contracts->add(c);
    }
}

void Application::saveContracts(const String& file) const {
    if(!this->contracts) {
        return;
    }
    ofstream os(file, ios::out | ios::trunc);
    StreamUtils::write(os, this->contracts->size());

    ConstIterator<Contract> it(*this->contracts);
    while(!it.end()) {
        ((Contract) it++).save(os);
    }
}

void Application::loadModels(const String& file) {
    Sanity::truthness(this->models == NULL, "Models are already loaded");

    this->models = new List<Model>();
    ifstream is(file, ios::in);
    List<String> l;

    cerr << time("Application") << "Loading models from " << file << endl;
    StreamUtils::skipLine(is); // Validate file format?
    while(is.peek() != EOF) {
        l = StreamUtils::readCSVLine(is, 4);
        ConstIterator<String> it(l);
        String name(&it++);
        int power = (&it++).toInt();
        bool diesel = (&it++).toBool();
        float baseCost = (&it).toFloat();
        this->models->add(Model(name, power, diesel, baseCost));
    }
    cerr << time("Application") << this->models->size() << " models loaded" << endl;
}

void Application::loadOptions(const String& file) {
    Sanity::truthness(this->models == NULL, "Options are already loaded");

    this->options = new List<Option>();
    ifstream is(file, ios::in);
    List<String> l;

    cerr << time("Application") << "Loading options from " << file << endl;
    StreamUtils::skipLine(is); // Validate file format?
    while(is.peek() != EOF) {
        l = StreamUtils::readCSVLine(is, 3);
        ConstIterator<String> it(l);
        String code = it++;
        String name = it++;
        int price = (&it).toInt();
        this->options->add(Option(code, name, price));
    }
    cerr << time("Application") << this->options->size() << " options loaded" << endl;
}


bool Application::login() {
    cout << "    ========================" << endl;
    cout << "    =        Login         =" << endl;
    cout << "    ========================" << endl << endl;
    cout << "    Entrez votre nom d'utilisateur: ";
    String username, password;
    cin >> username;
    cout << "    Entrez votre mot de passe: ";
    cin >> password;

    cerr << time("Application") << "Looking for '" << username << "'" << endl;

    Optional<Employee> optEmployee = this->users->getFirstMatching(LoginPredicate(username));
    if(optEmployee.hasValue()) {
        // Password not set
        if(optEmployee.get().getPassword().length() == 0) {
            cerr << time("Application") << "Found user without password, logging in and asking password" << endl;
            this->currentUser = &optEmployee.get();
            String newPassword;
            String confirmation;
            while(true) {
                cout << "    404 password not found, enter a new one: ";
                cin >> newPassword;
                cout << "    Confirm your password: ";
                cin >> confirmation;
                if(newPassword != confirmation) {
                    cout << " > Passwords don't match!" << endl;
                    continue;
                }
                try {
                    this->currentUser->setPassword(newPassword);
                } catch(InvalidPasswordException e) {
                    e.display();
                    continue;
                }
                break;
            }
            return true;
        }
        // Correct password
        if(optEmployee.get().getPassword() == password) {
            cerr << time("Application") << "Found correct user, logging in" << endl;
            this->currentUser = &optEmployee.get();
            return true;
        }

        cerr << time("Application") << "Found user (" << optEmployee.get().getLogin() << ") with wrong password" << endl;
        return false;
    } else {
        cerr << time("Application") << "User not found" << endl;
        return false;
    }
}

Employee& Application::getCurrentUser() const {
    return *this->currentUser;
}

bool Application::shouldQuit() const {
    return this->quitFlag;
}

void Application::changePassword() {
    String password;
    cout << "    Type your new password: ";
    cin >> password;
    try {
        this->currentUser->setPassword(password);
    } catch(InvalidPasswordException e) {
        cout << e.what() << endl;
        return;
    }
}

void Application::quit() {
    this->quitFlag = true;
}

void Application::displayUsers() {
    if(this->users->size() == 0) {
        cout << " > No users" << endl;
        return;
    }
    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        cout << it++ << endl;
    }
}

void Application::displayUser() {
    String username;
    cout << "    Enter the login of the user you're looking for: ";
    cin >> username;
    if(username.length() == 0) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = this->users->getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        cout << endl << "    = " << username << " =" << endl
            << "    Id: \t" << opt.get().getId() << endl
            << "    Login: \t" << opt.get().getLogin() << endl
            << "    Password: \t" << String("*", opt.get().getPassword().length()) << endl
            << "    Function: \t" << opt.get().getFunction() << endl
            << "    Firstname: \t" << opt.get().getFirstname() << endl
            << "    Surname: \t" << opt.get().getSurname() << endl;
    } else {
        cout << " > User not found :(" << endl;
    }
}

void Application::createUser() {
    String surname, firstname, login, id, func;
    int iId;
    bool bFunc;

    cout << endl << "    = Creating new user =" << endl;
    cout << "    User login: ";
    cin >> login;
    cout << "    User firstname: ";
    cin >> firstname;
    cout << "    User surname: ";
    cin >> surname;

    while(true) {
        cout << "    User id: ";
        cin >> id;
        try {
            iId = id.toInt();
        } catch(invalid_argument e) {
            cout << " > You didn't enter a valid int ._." << endl;
            continue;
        }
        break;
    }

    cout << "    Function (is " << Employee::ADMINISTRATIVE << "?): ";
    cin >> func;
    bFunc = func.toBool();


    if(this->users->containsWithPredicate(IdPredicate<Employee>(iId))) {
        cout << " > There is already a user with the id " << iId << endl;
        return;
    }
    if(this->users->containsWithPredicate(LoginPredicate(login))) {
        cout << " > There is already a user with the username " << login << endl;
        return;
    }

    this->users->add(Employee(surname, firstname, iId, login, bFunc ? Employee::ADMINISTRATIVE : Employee::SELLER));
    cout << " > User successfuly added" << endl;
}

void Application::resetPassword() {
    String username;
    cout << "    Enter the login of the user you want to reset the pwd for: ";
    cin >> username;
    if(username.length() == 0) {
        cout << " > Bad username" << endl;
        return;
    }

    Optional<Employee> opt = this->users->getFirstMatching(LoginPredicate(username));
    if(opt.hasValue()) {
        opt.get().resetPassword();
        cout << " > Password reset for " << username << endl;
    } else {
        cout << " > User not found :(" << endl;
    }
}

void Application::displayContracts() {
    if(this->contracts->size() == 0) {
        cout << " > No contracts" << endl;
        return;
    }

    ConstIterator<Contract> it(*this->contracts);
    while(!it.end()) {
        cout << "    " << it++ << endl;
    }
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

    Optional<Contract> opt = this->contracts->getFirstMatching(IdPredicate<Contract>(id));
    if(opt.hasValue()) {
        cout << "    " << opt.get() << endl;
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

    Optional<Employee> optEmployee = this->users->getFirstMatching(IdPredicate<Employee>(id));
    if(!optEmployee.hasValue()) {
        cout << " > There is no seller with this id" << endl;
        return;
    }
    if(optEmployee.get().getFunction() == Employee::ADMINISTRATIVE) {
        cout << " > This employee is not a seller" << endl;
        return;
    }

    bool stuffWasDisplayed = false;
    ConstIterator<Contract> contractIt(*this->contracts);
    while(!contractIt.end()) {
        if((&contractIt).getSellerId() == id) {
            cout << "    " << contractIt << endl;
            stuffWasDisplayed = true;
        }
    }

    if(!stuffWasDisplayed) {
        cout << " > No contracts for this seller" << endl;
    }
}

void Application::createClient() {
    String id, address, firstname, surname;
    int iId;
    cout << endl << "    = Creating new client =" << endl;
    while(true) {
        cout << "    Enter client id: ";
        cin >> id;
        try {
            iId = id.toInt();
        } catch(invalid_argument e) {
            cout << " > Invalid number given" << endl;
            continue;
        }
        break;
    }
    cout << "    Enter client address: ";
    cin >> address;
    cout << "    Enter client firstname: ";
    cin >> firstname;
    cout << "    Enter client surname";
    cin >> surname;

    if(this->clients->containsWithPredicate(IdPredicate<Client>(iId))) {
        cout << " > There is already a client with the id " << iId << endl;
        return;
    }
    this->clients->add(Client(surname, firstname, iId, address));
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

    if(this->contracts->containsWithPredicate(ClientIdPredicate(id))) {
        cout << " > Client is involved in a contract and can't be removed" << endl;
        return;
    }

    Iterator<Client> clientIt(*this->clients);
    while(!clientIt.end()) {
        if((&clientIt).getId() == id) {
            clientIt.remove();
            cout << " > Client removed" << endl;
            return;
        }
    }
    cout << " > Client not found" << endl;
}

void Application::displayClients() {
    if(this->clients->size() == 0) {
        cout << " > No clients" << endl;
        return;
    }

    ConstIterator<Client> it(*this->clients);
    while(!it.end()) {
        cout << "    " << &(it++) << endl;
    }
}

void Application::displayModels() {
    if(!this->models) {
        cout << " > Models not loaded" << endl;
        return;
    }

    if(this->models->size() == 0) {
        cout << " > No models yet" << endl;
        return;
    }

    int i = 0;
    ConstIterator<Model> it(*this->models);
    while(!it.end()) {
        cout << "    " << i++ << ". " << it++ << endl;
    }
}

void Application::displayOptions() {
    if(!this->options) {
        cout << " > Options not loaded" << endl;
        return;
    }

    if(this->options->size() == 0) {
        cout << " > No options yet" << endl;
        return;
    }

    ConstIterator<Option> it(*this->options);
    while(!it.end()) {
        cout << "    " << it++ << endl;
    }
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

    if(modelId >= this->models->size()) {
        cout << " > Model not found";
        return;
    }

    this->currentCar = new Car(carName, this->models->get(modelId));
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

    String input;
    cout << "    Enter the name of the project to load: ";
    cin >> input;
    this->currentCar->load(input);
    this->carDirty = false;
    cout << " > Car loaded" << endl;
}

void Application::displayCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }
    cout << "    " << *this->currentCar << endl;
}

void Application::addOptionToCurrentCar() {
    if(!this->currentCar) {
        cout << " > No car currently loaded" << endl;
        return;
    }

    String input;
    cout << "    Enter the code of the option to add: ";
    cin >> input;

    Optional<Option> opt = this->options->getFirstMatching(CodePredicate(input));
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
    int contractId, clientId;

    while(true) {
        cout << "    Enter the id of the contract: ";
        cin >> input;
        try {
            contractId = input.toInt();
        } catch(invalid_argument e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    if(this->contracts->containsWithPredicate(IdPredicate<Contract>(contractId))) {
        cout << " > A contract already exists with this id" << endl;
        return;
    }

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

    cout << "    Enter the name of the car project: ";
    cin >> carName;

    Car* car;
    if(this->currentCar && this->currentCar->getName() == carName) {
        car = this->currentCar;
    } else {
        car = new Car();
        try {
            car->load(String("data/") + carName + ".car");
        } catch(AssertionException e) {
            cout << e.what() << endl;
            return;
        }
    }

    this->contracts->add(Contract(contractId, this->currentUser->getId(), clientId, Date(), car));
    cout << " > Contract added" << endl;
}

void Application::displayContractsForCurrentUser() {
    bool displayedStuff = false;
    ConstIterator<Contract> it(*this->contracts);
    while(!it.end()) {
        if((&it).getSellerId() == this->currentUser->getId()) {
            cout << "    " << it << endl;
            displayedStuff = true;
        }
        ++it;
    }
    if(!displayedStuff) {
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

    Optional<Contract> opt = this->contracts->getFirstMatching(IdPredicate<Contract>(id));
    if(!opt.hasValue()) {
        cout << " > Contract not found" << endl;
        return;
    }

    int choice;
    while(true) {
        cout << "    What do you want to modify? (1=discount, 2=car, 0=done) ";
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
                cout << "    Enter the new discount";
                cin >> input;
                float discount;
                try {
                    discount = input.toFloat();
                } catch(invalid_argument e) {
                    cout << " > " << e.what() << endl;
                    continue;
                }
                opt.get().setDiscount(discount);
                break;
            case 2:
                cout << "    Enter the name of the new car project: ";
                cin >> input;
                if(this->currentCar->getName() == input) {
                    opt.get().setCar(this->currentCar);
                } else {
                    Car* car = new Car();
                    try {
                        car->load(String("data/") + input + ".car");
                    } catch(AssertionException e) {
                        cout << e.what() << endl;
                        continue;
                    }
                    opt.get().setCar(car);
                }
            default:
                cout << " > Invalid choice" << endl;
        }
    }
}
