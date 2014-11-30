#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>

#include "Employee.hpp"
#include "collections/SortedList.hpp"
#include "menu/Menu.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Application {

private:
    SortedList<Employee>* users;
    Employee* currentUser;
    bool quitFlag;

public:
    Application();
    ~Application();

    void loadUsers(const String&);
    void defaultUsers();
    void saveUsers(const String&) const;
    bool login();
    void logout();
    bool isUserLoggedin() const;
    Employee& getCurrentUser() const;
    bool shouldQuit() const;

    // Menu actions
    void dummy() { cout << "dummy" << endl; };
    void changePassword();
    void displayUserSummary();
    void quit();

};

#endif