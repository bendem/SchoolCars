#include "Person.hpp"

const String& Person::getFirstname() const {
    return this->firstname;
}

void Person::setFirstname(const String& firstname) {
    this->firstname = firstname;
}

const String& Person::getSurname() const {
    return this->surname;
}

void Person::setSurname(const String& surname) {
    this->surname = surname;
}

void Person::display() const {
    cout << this->toString() << endl;
}

String Person::toString() const {
    return (String) "Person{firstname: '" + this->firstname + "', surname:'" + this->surname + "'}";
}

bool Person::operator>(const Person& param) const {
    if(this->surname == param.surname) {
        return this->firstname > param.firstname;
    }
    return this->surname > param.surname;
}

bool Person::operator<(const Person& param) const {
    if(this->surname == param.surname) {
        return this->firstname < param.firstname;
    }
    return this->surname < param.surname;
}

bool Person::operator<=(const Person& param) const {
    return *this < param || *this == param;
}

bool Person::operator>=(const Person& param) const {
    return *this > param || *this == param;
}

bool Person::operator==(const Person& param) const {
    return this->surname == param.surname && this->firstname == param.firstname;
}

bool Person::operator!=(const Person& param) const {
    return this->surname != param.surname || this->firstname != param.firstname;
}

istream& operator>>(istream& is, Person& p) {
    return is >> p.firstname >> p.surname;
}

ostream& operator<<(ostream& os, const Person& p) {
    return os << p.toString();
}
