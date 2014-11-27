#include "Car.hpp"

Car::Car(String name, Model model) : name(name), model(model) {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        options[i] = NULL;
    }
}

Car::Car(Car const& param) : name(param.name), model(param.model) {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        this->options[i] = param.options[i] ? new Option(*param.options[i]) : NULL;
    }
}

void Car::display() const {
    cout << *this << endl;
}

void Car::addOption(const Option& option) {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(!this->options[i]) {
            this->options[i] = new Option(option);
            return;
        }
    }
    throw NotEnoughSpaceException();
}

void Car::removeOption(const String& option) {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i] && this->options[i]->getCode() == option) {
            delete this->options[i];
            this->options[i] = NULL;
            return;
        }
    }
    throw ElementNotFoundException(option + " was not found");
}

float Car::getPrice() const {
    float price = 0;
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i] != NULL) {
            price += this->options[i]->getPrice();
        }
    }
    return price;
}

String Car::getName() const {
    return this->name;
}

void Car::setName(String name) {
    this->name = name;
}

const Model& Car::getModel() const {
    return this->model;
}

void Car::setModel(const Model& model) {
    this->model = model;
}

void Car::save() const {
    ofstream os(this->name + ".car", ios::out);

    StreamUtils::write(os, this->name);
    this->model.save(os);

    // Save the position of the option count
    long pos = os.tellp();

    // Skip int size so we can write the count later
    StreamUtils::write(os, 0);

    int count = 0;
    // Write  the options and count them
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) {
            this->options[i]->save(os);
            ++count;
        }
    }

    // Get back to the saved position and write option count
    os.seekp(pos);
    StreamUtils::write(os, count);
}

void Car::load(const String& filename) {
    ifstream is(filename, ios::in);
    this->name = StreamUtils::readString(is);
    this->model.load(is);

    int count = StreamUtils::readInt(is);
    for(int i = 0; i < count; ++i) {
        if(!this->options[i]) {
            this->options[i] = new Option();
        }
        this->options[i]->load(is);
    }
}

Car& Car::operator=(const Car& param) {
    this->name = param.name;
    this->model = param.model;

    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) {
            delete this->options[i];
        }
        this->options[i] = param.options[i] ? new Option(*param.options[i]) : NULL;
    }

    return *this;
}

Car Car::operator+(const Option& param) const {
    Car tmp(*this);
    tmp.addOption(param);
    return tmp;
}

Car Car::operator-(const Option& param) const {
    Car tmp(*this);
    tmp.removeOption(param.getCode());
    return tmp;
}

Car Car::operator-(const String& param) const {
    Car tmp(*this);
    tmp.removeOption(param);
    return tmp;
}

bool Car::operator>(const Car& param) {
    return this->getPrice() > param.getPrice();
}

bool Car::operator<(const Car& param) {
    return this->getPrice() < param.getPrice();
}

bool Car::operator==(const Car& param) {
    return this->getPrice() == param.getPrice();
}

ostream& operator<<(ostream& os, const Car& car) {
    os  << "Name: '" << car.name << "', Model{" << car.model << "}, Options[";
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(car.options[i]) {
            os << "Option{" << *car.options[i] << "}, ";
        }
    }
    return os << "]";
}

istream& operator>>(istream& is, Car& car) {
    return is;
}
