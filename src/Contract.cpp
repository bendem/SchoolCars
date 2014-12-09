#include "Contract.hpp"

Contract::Contract() {
    this->car = NULL;
}

Contract::Contract(int id, int sellerId, int clientId, const Date& date, Car* car, float discount)
    : id(id), sellerId(sellerId), clientId(clientId), date(date), car(new Car(*car)), discount(discount) {}

Contract::~Contract() {
    if(this->car) {
        delete this->car;
    }
}

int Contract::getId() const {
    return this->id;
}

int Contract::getSellerId() const {
    return this->sellerId;
}

int Contract::getClientId() const {
    return this->clientId;
}

const Date& Contract::getDate() const {
    return this->date;
}

Date& Contract::getDate() {
    return this->date;
}

Car* Contract::getCar() const {
    return this->car;
}

void Contract::setCar(Car* car) {
    if(this->car) {
        delete this->car;
    }
    this->car = new Car(*car);
}

float Contract::getDiscount() const {
    return this->discount;
}

void Contract::setDiscount(float discount) {
    this->discount = discount;
}

bool Contract::operator==(const Contract& param) const {
    return this->date == param.date;
}

bool Contract::operator!=(const Contract& param) const {
    return this->date != param.date;
}

bool Contract::operator>(const Contract& param) const {
    return this->date > param.date;
}

bool Contract::operator<(const Contract& param) const {
    return this->date < param.date;
}

bool Contract::operator>=(const Contract& param) const {
    return this->date >= param.date;
}

bool Contract::operator<=(const Contract& param) const {
    return this->date <= param.date;
}

void Contract::save(ostream& os) const {
    StreamUtils::write(os, this->id);
    StreamUtils::write(os, this->sellerId);
    StreamUtils::write(os, this->clientId);
    date.save(os);
    StreamUtils::write(os, this->car->getName());
    //car->save();
    StreamUtils::write(os, this->discount);
}

void Contract::load(istream& is) {
    this->id = StreamUtils::readInt(is);
    this->sellerId = StreamUtils::readInt(is);
    this->clientId = StreamUtils::readInt(is);
    String carName = StreamUtils::readString(is);
    if(this->car) {
        delete this->car;
    }
    this->car = new Car();
    this->car->load(carName);
    this->discount = StreamUtils::readFloat(is);
}

ostream& operator<<(ostream& os, const Contract& param) {
    return os
        << "Contract{"
        << "id=" << param.id
        << ", sellerId=" << param.sellerId
        << ", clientId=" << param.clientId
        << ", date='" << param.date << "'"
        << ", car=" << *param.car
        << ", discount=" << param.discount
        << "}";
}
