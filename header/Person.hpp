#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <fstream>

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

    virtual void save(ofstream&) const;
    virtual void load(ifstream&);

    void display() const;
    virtual String toString() const;

    Person& operator=(const Person&);

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
