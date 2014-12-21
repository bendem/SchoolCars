#include <utils/StreamUtils.hpp>
#include "Option.hpp"

Option::Option(String code, String name, float price) {
    this->code = code;
    this->name = name;
    this->price = price;
}

Option::Option(const Option& param) {
    this->code = param.code;
    this->name = param.name;
    this->price = param.price;
}

void Option::display() const {
    cout << *this << endl;
}

String Option::getCode() const {
    return code;
}

void Option::setCode(String code) {
    this->code = code;
}

String Option::getName() const {
    return this->name;
}

void Option::setName(String name) {
    this->name = name;
}

float Option::getPrice() const {
    return this->price;
}

void Option::setPrice(float price) {
    this->price = price;
}

void Option::save(ostream& os) const {
    StreamUtils::write(os, this->code);
    StreamUtils::write(os, this->name);
    StreamUtils::write(os, this->price);
}

void Option::load(istream& is) {
    this->code = StreamUtils::readString(is);
    this->name = StreamUtils::readString(is);
    this->price = StreamUtils::readFloat(is);
}

Option& Option::operator++() {
    this->price += 50;
    return *this;
}

Option Option::operator++(int) {
    Option tmp(*this);
    this->price += 50;
    return tmp;
}

Option& Option::operator--() {
    this->price -= 50;
    return *this;
}

Option Option::operator--(int) {
    Option tmp(*this);
    this->price -= 50;
    return tmp;
}

Option& Option::operator=(const Option& param) {
    this->code = param.code;
    this->name = param.name;
    this->price = param.price;
    return *this;
}

istream& operator>>(istream& is, Option& option) {
    return is >> option.code >> option.name >> option.price;
}

ostream& operator<<(ostream& os, const Option& option) {
    return os << "Code: '" << option.code << "', Name: '" << option.name << "', Price: " << option.price;
}

bool Option::operator==(const Option& param) const {
    return this->name == param.name
        && this->code == param.code
        && this->price == param.price;
}
