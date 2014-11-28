#include "Person.hpp"

Person::Person(const Person& param) {
    this->firstname = param.firstname;
    this->surname = param.surname;
}

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

void Person::save(ofstream& os) const {
    StreamUtils::write(os, this->firstname);
    StreamUtils::write(os, this->surname);
}

void Person::load(ifstream& is) {
    this->firstname = StreamUtils::readString(is);
    this->surname = StreamUtils::readString(is);
}

void Person::display() const {
    cout << this->toString() << endl;
}

String Person::toString() const {
    return (String) "Person{firstname: '" + this->firstname + "', surname: '" + this->surname + "'}";
}

Person& Person::operator=(const Person& param) {
    this->firstname = param.firstname;
    this->surname = param.surname;
    return *this;
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
