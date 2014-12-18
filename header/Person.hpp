#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

#include "utils/StreamUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Person {

protected:
    String firstname;
    String surname;

public:
    Person(const String& surname = "", const String& firstname = "") : surname(surname), firstname(firstname) {}
    Person(const Person&);

    const String& getFirstname() const;
    void setFirstname(const String& firstname);

    const String& getSurname() const;
    void setSurname(const String& surname);

    virtual void save(ostream&) const;
    virtual void load(istream&);

    void display() const;
    virtual String toString() const;

    Person& operator=(const Person&);

    friend istream& operator>>(istream&, Person&);
    friend ostream& operator<<(ostream&, const Person&);

};

#endif
