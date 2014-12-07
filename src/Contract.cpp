#include "Contract.hpp"

Contract::Contract(int id, int sellerId, int clientId, const Date& date, Car* car, float discount)
    : id(id), sellerId(sellerId), clientId(clientId), date(date), car(car), discount(discount) {}

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

float Contract::getDiscount() const {
    return this->discount;
}
