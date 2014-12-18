#include "Client.hpp"

Client::Client(const Client& param) : Person(param) {
    this->id = param.id;
    this->address = param.address;
}

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

int Client::compareTo(const Client& param) const {
    int res = this->surname.compareTo(param.surname);
    if(res == 0) {
        return this->firstname.compareTo(param.firstname);
    }
    return res;
}

Client& Client::operator=(const Client& param) {
    this->id = param.id;
    this->address = param.address;
    Person::operator=(param);
    return *this;
}

void Client::load(istream& is) {
    this->id = StreamUtils::readInt(is);
    this->address = StreamUtils::readString(is);
    Person::load(is);
}

void Client::save(ostream& os) const {
    StreamUtils::write(os, this->id);
    StreamUtils::write(os, this->address);
    Person::save(os);
}

istream& operator>>(istream& is, Client& param) {
    return is >> param.id >> param.address >> (Person&) param;
}

ostream& operator<<(ostream& os, const Client& param) {
    return os << param.toString();
}
