#include "Client.hpp"

int Client::getId() const {
    return this->id;
}

void Client::setId(int id) {
    this->id = id;
}

const String& Client::getAddress() const {
    return this->address;
}

void Client::setAddress(const String& address) {
    this->address = address;
}

String Client::toString() const {
    stringstream s;
    s << "Client{id: " << this->id
        << ", address: " << this->address
        << ", " << Person::toString() << "}";
    return s.str();
}

istream& operator>>(istream& is, Client& param) {
    return is >> param.id >> param.address >> (Person&) param;
}

ostream& operator<<(ostream& os, const Client& param) {
    return os << param.toString();
}
