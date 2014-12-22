#include "Contract.hpp"

Contract::Contract() {
    this->car = NULL;
}

Contract::Contract(unsigned int id, unsigned int sellerId, unsigned int clientId, const Date& date, const Car& car, float discount)
    : id(id), sellerId(sellerId), clientId(clientId), date(date), car(new Car(car)), discount(discount) {}

Contract::Contract(const Contract& p) {
    this->id = p.id;
    this->sellerId = p.sellerId;
    this->clientId = p.clientId;
    this->date = p.date;
    this->car = new Car(*p.car);
    this->discount = p.discount;
}

Contract::~Contract() {
    if(this->car) {
        delete this->car;
    }
}

unsigned int Contract::getId() const {
    return this->id;
}

unsigned int Contract::getSellerId() const {
    return this->sellerId;
}

unsigned int Contract::getClientId() const {
    return this->clientId;
}

const Date& Contract::getDate() const {
    return this->date;
}

Date& Contract::getDate() {
    return this->date;
}

const Car& Contract::getCar() const {
    Sanity::nullness(this->car, "Car is null, can't dereference pointer");

    return *this->car;
}

Car& Contract::getCar() {
    Sanity::nullness(this->car, "Car is null, can't dereference pointer");

    return *this->car;
}

void Contract::setCar(const Car& car) {
    if(this->car) {
        delete this->car;
    }
    this->car = new Car(car);
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

Contract& Contract::operator=(Contract p) {
    this->id = p.id;
    this->sellerId = p.sellerId;
    this->clientId = p.clientId;
    this->date = p.date;
    swap(this->car, p.car);
    this->discount = p.discount;

    return *this;
}

void Contract::save(ostream& os) const {
    Sanity::nullness(this->car, "Can't save null car");

    StreamUtils::write(os, this->id);
    StreamUtils::write(os, this->sellerId);
    StreamUtils::write(os, this->clientId);
    date.save(os);
    StreamUtils::write(os, this->car->getName());
    //car->save();
    StreamUtils::write(os, this->discount);
}

void Contract::load(istream& is) {
    this->id = StreamUtils::read<unsigned int>(is);
    this->sellerId = StreamUtils::read<unsigned int>(is);
    this->clientId = StreamUtils::read<unsigned int>(is);
    date.load(is);
    String carName = StreamUtils::readString(is);
    if(this->car) {
        delete this->car;
    }
    this->car = new Car();
    this->car->load(String("data/") + carName + ".car");
    this->discount = StreamUtils::read<float>(is);
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
