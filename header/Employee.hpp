#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <fstream>
#include <sstream>

#include "Person.hpp"
#include "exceptions/InvalidFunctionException.hpp"
#include "exceptions/InvalidPasswordException.hpp"
#include "utils/StreamUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Employee : public Person {

private:
    int id;
    String login;
    String password;
    String function;

    void checkPassword(const String&) const;

public:
    const static String SELLER;
    const static String ADMINISTRATIVE;

    Employee(String surname = "", String firstname = "", int id = 0, String login = "", String function = "") :
        Person(firstname, surname), id(id), login(login), password(""), function(function) {}
    Employee(const Employee&);

    int getId() const;
    void setId(int id);

    const String& getLogin() const;
    void setLogin(const String& login);

    const String& getPassword() const;
    void setPassword(const String& password);
    void resetPassword();

    const String& getFunction() const;
    void setFunction(const String& function);

    void save(ofstream&) const;
    void load(ifstream&);

    String toString() const;

    Employee& operator=(const Employee&);

    bool operator>(const Employee&) const;
    bool operator<(const Employee&) const;
    bool operator<=(const Employee&) const;
    bool operator>=(const Employee&) const;
    bool operator==(const Employee&) const;
    bool operator!=(const Employee&) const;

    friend istream& operator>>(istream&, Employee&);
    friend ostream& operator<<(ostream&, const Employee&);

};

#endif
