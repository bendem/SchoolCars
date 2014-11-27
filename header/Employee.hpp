#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <sstream>

#include "exceptions/InvalidFunctionException.hpp"
#include "exceptions/InvalidPasswordException.hpp"
#include "Person.hpp"
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
    static const String SELLER;
    static const String ADMINISTRATIVE;

    Employee(String surname = "", String firstname = "", int id = 0, String login = "", String function = "") :
        Person(firstname, surname), id(id), login(login), password(""), function(function) {}

    int getId() const;
    void setId(int id);

    const String& getLogin() const;
    void setLogin(const String& login);

    const String& getPassword() const;
    void setPassword(const String& password);

    const String& getFunction() const;
    void setFunction(const String& function);

    String toString() const;

    friend istream& operator>>(istream&, Employee&);
    friend ostream& operator<<(ostream&, const Employee&);

};

#endif
