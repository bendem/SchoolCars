#include "Application.hpp"

Application::Application() {
    this->users = NULL;
    this->currentUser = NULL;
    this->quitFlag = false;
}

Application::~Application() {
    if(this->users) {
        delete this->users;
    }
    if(this->currentUser) {
        delete this->currentUser;
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

    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getLogin() == username) {
            // Password not set
            if((&it).getPassword().length() == 0) {
                cerr << time << "Found user without password, logging in and asking password" << endl;
                this->currentUser = new Employee(&it);
                // TODO Ask for password
                return true;
            }
            // Correct password
            if((&it).getPassword() == password) {
                cerr << time << "Found correct user, logging in" << endl;
                this->currentUser = new Employee(&it);
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

bool Application::shouldQuit() const {
    return this->quitFlag;
}

void Application::changePassword() {
    String password;
    cout << "Type your new password: ";
    cin >> password;
    try {
        this->currentUser->setPassword(password);
    } catch(InvalidPasswordException e) {
        cout << e.getMessage() << endl;
        return;
    }

    Iterator<Employee> it(*this->users);
    while(!it.end()) {
        if((&it).getLogin() == this->currentUser->getLogin()) {
            (&it).setPassword(password);
            cout << "> Password changed" << endl;
            return;
        }
        ++it;
    }
}

void Application::displayUserSummary() {
    ConstIterator<Employee> it(*this->users);
    while(!it.end()) {
        cout << &it << endl;
        ++it;
    }
}

void Application::quit() {
    this->quitFlag = true;
}
