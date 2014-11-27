#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

#include "utils/String.hpp"

using namespace std;

class Person {

private:
    String firstname;
    String surname;

public:
    Person(const String& surname = "", const String& firstname = "") : surname(surname), firstname(firstname) {}

    const String& getFirstname() const;
    void setFirstname(const String& firstname);

    const String& getSurname() const;
    void setSurname(const String& surname);

    void display() const;
    virtual String toString() const;

    bool operator>(const Person&) const;
    bool operator<(const Person&) const;
    bool operator<=(const Person&) const;
    bool operator>=(const Person&) const;
    bool operator==(const Person&) const;
    bool operator!=(const Person&) const;

    friend istream& operator>>(istream&, Person&);
    friend ostream& operator<<(ostream&, const Person&);

};

#endif
