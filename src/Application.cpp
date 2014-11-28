#include "Application.hpp"

Application::Application() {
    this->users = NULL;
    this->currentUser = NULL;
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
    Employee e("admin", "admin", 0, "admin", Employee::ADMINISTRATIVE);
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

void Application::login() {

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
