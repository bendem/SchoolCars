#include "Employee.hpp"

const String Employee::SELLER = "Vendeur";
const String Employee::ADMINISTRATIVE = "Administratif";

void Employee::checkPassword(const String& pass) const {
    if(pass.length() < 8) {
        throw InvalidPasswordException("Password should have at least 8 characters");
    }

    bool foundInt = false, foundLetter = false;
    for(int i = 0; i < pass.length(); ++i) {
        if(pass[i] >= '0' && pass[i] <= '9') {
            foundInt = true;
        } else if(pass[i] >= 'a' && pass[i] <= 'z' || pass[i] >= 'A' && pass[i] <= 'Z') {
            foundLetter = true;
        }

        if(foundInt && foundLetter) {
            return;
        }
    }

    if(!foundInt || !foundLetter) {
        throw InvalidPasswordException("Password should contain at least one digit and one letter");
    }
}

int Employee::getId() const {
    return this->id;
}

void Employee::setId(int id) {
    this->id = id;
}

const String& Employee::getLogin() const {
    return this->login;
}

void Employee::setLogin(const String& login) {
    this->login = login;
}

const String& Employee::getPassword() const {
    return this->password;
}

void Employee::setPassword(const String& password) {
    checkPassword(password);
    this->password = password;
}

const String& Employee::getFunction() const {
    return this->function;
}

void Employee::setFunction(const String& function) {
    if(function == Employee::ADMINISTRATIVE || function == Employee::SELLER) {
        this->function = function;
    } else {
        throw InvalidFunctionException(function + " is not a valid function");
    }
}

String Employee::toString() const {
    stringstream s;
    s << "Employee{id: " << this->id
        << ", login: " << this->login
        << ", password: '" << String('*', this->password.length()) << "'"
        << ", " << Person::toString() << "}";
    return s.str();
}

istream& operator>>(istream& is, Employee& param) {
    return is >> param.id >> param.login >> param.password >> param.function >> (Person&) param;
}

ostream& operator<<(ostream& os, const Employee& param) {
    return os << param.toString();
}
