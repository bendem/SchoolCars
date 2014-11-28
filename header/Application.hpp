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

public:
    Application();
    ~Application();

    void loadUsers(const String&);
    void defaultUsers();
    void saveUsers(const String&) const;
    void login();
    void logout();
    bool isUserLoggedin() const;
    Employee& getCurrentUser() const;
    bool dummy() { cout << "dummy" << endl; return true; };

};

#endif
