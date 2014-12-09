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
    // Points directly inside this->users, has already been deleted
    // if(this->currentUser) {
    //     delete this->currentUser;
    // }
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
    for (int i = 0; i < count; ++i) {
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
    for (int i = 0; i < count; ++i) {
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
    for (int i = 0; i < count; ++i) {
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

    cerr << time << "Loading models from " << file << endl;
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
    cerr << time << this->models->size() << " models loaded" << endl;
}

void Application::loadOptions(const String& file) {
    Sanity::truthness(this->models == NULL, "Options are already loaded");

    this->options = new List<Option>();
    ifstream is(file, ios::in);
    List<String> l;

    cerr << time << "Loading options from " << file << endl;
    StreamUtils::skipLine(is); // Validate file format?
    while(is.peek() != EOF) {
        l = StreamUtils::readCSVLine(is, 3);
        ConstIterator<String> it(l);
        String code = it++;
        String name = it++;
        int price = (&it).toInt();
        this->options->add(Option(code, name, price));
    }
    cerr << time << this->options->size() << " options loaded" << endl;
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

    cerr << time << "Looking for '" << username << "'" << endl;

    Iterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getLogin() == username) {
            // Password not set
            if((&it).getPassword().length() == 0) {
                cerr << time << "Found user without password, logging in and asking password" << endl;
                this->currentUser = &(&it);
                String newPassword;
                while(true) {
                    cout << "    404 password not found, enter a new one: ";
                    cin >> newPassword;
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
            if((&it).getPassword() == password) {
                cerr << time << "Found correct user, logging in" << endl;
                this->currentUser = &(&it);
                return true;
            }

            cerr << time << "Found user (" << (&it).getLogin() << ") with wrong password" << endl;
            return false;
        }
        ++it;
    }
    cerr << time << "User not found" << endl;
    return false;
}

void Application::logout() {
    delete this->currentUser;
    this->currentUser = NULL;
}

bool Application::isUserLoggedin() const {
    return this->currentUser != NULL;
}

Employee& Application::getCurrentUser() const {
    return *this->currentUser;
}

bool Application::isThereACarAtTheMomemnt() const {
    return this->currentCar != NULL;
}

Car& Application::getCurrentCar() const {
    return *this->currentCar;
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

    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getLogin() == username) {
            cout << endl << "    = " << username << " =" << endl
                << "    Id: \t" << (&it).getId() << endl
                << "    Login: \t" << (&it).getLogin() << endl
                << "    Password: \t" << String("*", (&it).getPassword().length()) << endl
                << "    Function: \t" << (&it).getFunction() << endl
                << "    Firstname: \t" << (&it).getFirstname() << endl
                << "    Surname: \t" << (&it).getSurname() << endl;
            return;
        }
        ++it;
    }
    cout << " > User not found :(" << endl;
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
        } catch (invalid_argument e) {
            cout << " > You didn't enter a valid int ._." << endl;
            continue;
        }
        break;
    }

    cout << "    Function (is " << Employee::ADMINISTRATIVE << "?): ";
    cin >> func;
    bFunc = func.toBool();

    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getId() == iId) {
            cout << " > There is already a user with the id " << iId << endl;
            return;
        }
        if((&it).getLogin() == login) {
            cout << " > There is already a user with the username " << login << endl;
            return;
        }
        ++it;
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

    Iterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getLogin() == username) {
            (&it).resetPassword();
            cout << " > Password reset for " << username << endl;
            return;
        }
        ++it;
    }
    cout << " > User not found :(" << endl;
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

    ConstIterator<Contract> it(*this->contracts);
    while(!it.end()) {
        if((&it).getId() == id) {
            cout << "    " << it << endl;
            return;
        }
        ++it;
    }
    cout << " > id not found" << endl;
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

    bool found = false;
    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getId() == id) {
            if((&it).getFunction() == Employee::ADMINISTRATIVE) {
                cout << " > This employee is not a seller" << endl;
                return;
            }
            found = true;
            break;
        }
    }

    if(!found) {
        cout << " > There is no seller with this id" << endl;
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
        } catch (invalid_argument e) {
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
    ConstIterator<Client> it(*this->clients);
    while(!it.end()) {
        if((&it).getId() == iId) {
            cout << " > There is already a client with the id " << iId << endl;
            return;
        }
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

    ConstIterator<Contract> contractIt(*this->contracts);
    while (!contractIt.end()) {
        if ((&contractIt).getClientId() == id) {
            cout << " > Client is involved in a contract and can't be removed" << endl;
            return;
        }
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

    int i = 0;
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

    ConstIterator<Option> it(*this->options);
    while(!it.end()) {
        if((&it).getCode() == input) {
            try {
                this->currentCar->addOption(&it);
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
        }
    }

    cout << " > Option not found" << endl;
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
    //TODO
}

void Application::displayContractsForCurrentUser() {
    //TODO
}

void Application::modifyContract() {
    //TODO
}
