#include "Model.hpp"

Model::Model(Model const &param) {
    this->name = param.name;
    this->power = param.power;
    this->diesel = param.diesel;
    this->baseCost = param.baseCost;
}

void Model::display() const {
    cout << *this << endl;
}

float Model::getBaseCost() const {
    return baseCost;
}

void Model::setBaseCost(float baseCost) {
    this->baseCost = baseCost;
}

bool Model::isDiesel() const {
    return diesel;
}

void Model::setDiesel(bool diesel) {
    this->diesel = diesel;
}

const String& Model::getName() const {
    return name;
}

void Model::setName(const String& name) {
    this->name = name;
}

int Model::getPower() const {
    return power;
}

void Model::setPower(int power) {
    this->power = power;
}

Model& Model::operator=(const Model& param) {
    this->name = param.name;
    this->power = param.power;
    this->diesel = param.diesel;
    this->baseCost = param.baseCost;
    return *this;
}

bool Model::operator==(const Model& param) {
    return this->name == param.name;
}

void Model::save(ofstream& os) const {
    StreamUtils::write(os, this->name);
    StreamUtils::write(os, this->power);
    StreamUtils::write(os, this->diesel);
    StreamUtils::write(os, this->baseCost);
}

void Model::load(ifstream& is) {
    this->name = StreamUtils::readString(is);
    this->power = StreamUtils::readInt(is);
    this->diesel = StreamUtils::readBool(is);
    this->baseCost = StreamUtils::readFloat(is);
}

ostream& operator<<(ostream& os, const Model& model) {
    return os << "Power: " << model.power << ", Name: '" << model.name << "', diesel: "
        << (model.diesel ? "yes" : "no") << ", Base cost: " << model.baseCost;
}

istream& operator>>(istream& is, Model& model) {
    return is >> model.name >> model.power >> model.diesel >> model.baseCost;
}
