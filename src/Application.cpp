#include "Application.hpp"

Application::Application() {
    this->users = NULL;
    this->clients = new SortedList<Client>();
    this->models = NULL;
    this->options = NULL;
    this->currentUser = NULL;
    this->currentCar = NULL;
    this->quitFlag = false;
}

Application::~Application() {
    if(this->users) {
        delete this->users;
    }
    if(this->models) {
        delete this->models;
    }
    if(this->options) {
        delete this->options;
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
    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        cout << &it << endl;
        ++it;
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

    while(true) {
        cout << "    Function (is " << Employee::ADMINISTRATIVE << "?): ";
        cin >> func;
        try {
            bFunc = func.toBool();
        } catch (invalid_argument e) {
            cout << " > You didn't enter a valid int ._." << endl;
            continue;
        }
        break;
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
    // TODO
}

void Application::displayContract() {
    // TODO
}

void Application::displaySellerContracts() {
    // TODO
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
    this->clients->add(Client(surname, firstname, iId, address));
}

void Application::removeClient() {
    //TODO
}

void Application::displayClients() {
    //TODO
}

void Application::displayModels() {
    //TODO
}

void Application::displayOptions() {
    //TODO
}

void Application::createCar() {
    //TODO
}

void Application::loadCar() {
    //TODO
}

void Application::displayCurrentCar() {
    //TODO
}

void Application::addOptionToCurrentCar() {
    //TODO
}

void Application::removeOptionFromCurrentCar() {
    //TODO
}

void Application::applyDiscountToCurrentCar() {
    //TODO
}

void Application::saveCurrentCar() {
    //TODO
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
