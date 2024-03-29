#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <sstream>

#include "Person.hpp"
#include "exceptions/InvalidFunctionException.hpp"
#include "exceptions/InvalidPasswordException.hpp"
#include "utils/Comparable.hpp"
#include "utils/StreamUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Employee : public Person, public Comparable<Employee> {

private:
    unsigned int id;
    String login;
    String password;
    String function;

    void checkPassword(const String&) const;

public:
    const static String SELLER;
    const static String ADMINISTRATIVE;

    Employee(String surname = "", String firstname = "", unsigned int id = 0, String login = "", String function = "") :
        Person(surname, firstname), id(id), login(login), password(""), function(function) {}
    Employee(const Employee&);

    unsigned int getId() const;
    void setId(unsigned int id);

    const String& getLogin() const;
    void setLogin(const String& login);

    const String& getPassword() const;
    void setPassword(const String& password);
    void resetPassword();

    const String& getFunction() const;
    void setFunction(const String& function);

    void save(ostream&) const;
    void load(istream&);

    String toString() const;

    Employee& operator=(const Employee&);

    int compareTo(const Employee&) const;

    friend istream& operator>>(istream&, Employee&);
    friend ostream& operator<<(ostream&, const Employee&);

};

#endif
