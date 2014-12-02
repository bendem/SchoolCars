#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>

#include "Car.hpp"
#include "Client.hpp"
#include "Employee.hpp"
#include "collections/SortedList.hpp"
#include "menu/Menu.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Application {

private:
    SortedList<Employee>* users;
    SortedList<Client>* clients;
    Employee* currentUser;
    Car* currentCar;
    bool quitFlag;

public:
    Application();
    ~Application();

    void loadUsers(const String&);
    void defaultUsers();
    void saveUsers(const String&) const;
    void loadClients(const String&);
    void saveClients(const String&) const;
    bool login();
    void logout();
    bool isUserLoggedin() const;
    Employee& getCurrentUser() const;
    bool isThereACarAtTheMomemnt() const ;
    Car& getCurrentCar() const;
    bool shouldQuit() const;

    // Menu actions
    void dummy() { cout << "dummy" << endl; };
    void changePassword();
    void displayUserSummary();
    void displayUser();
    void createUser();
    void resetPassword();
    void quit();

};

#endif
