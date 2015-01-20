#include "Car.hpp"

Car::Car(String name, const Model& model) : name(name), model(model) {
    this->options = new Option*[MAX_OPTION_COUNT];
    ArrayUtils::fill<Option*>(this->options, NULL, MAX_OPTION_COUNT);
}

Car::Car(const Car& param) : Comparable<Car>(), name(param.name), model(param.model) {
    this->options = new Option*[MAX_OPTION_COUNT];
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        this->options[i] = param.options[i] ? new Option(*param.options[i]) : (Option*) NULL;
    }
}

Car::~Car() {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) {
            delete this->options[i];
        }
    }
    delete this->options;
}

void Car::display() const {
    cout << *this << endl;
}

void Car::addOption(const Option& option) {
    int added = -1;
    bool fail = false;
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(added == -1 && !this->options[i]) {
            this->options[i] = new Option(option);
            added = i;
            continue;
        }
        if(this->options[i] && this->options[i]->getCode() == option.getCode()) {
            fail = true;
            break;
        }
    }

    // Found the same after adding it
    if(fail) {
        if(added != -1) {
            delete this->options[added];
            this->options[added] = NULL;
        }
        throw AssertionException();
    }

    // Not added
    if(added == -1) {
        throw NotEnoughSpaceException();
    }
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

Option& Car::getOption(const String& code) {
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i] && this->options[i]->getCode() == code) {
            return *this->options[i];
        }
    }
    throw ElementNotFoundException();
}

List<Option> Car::getOptions() const {
    List<Option> l;
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) {
            l.add(*this->options[i]);
        }
    }
    return l;
}

float Car::getPrice() const {
    float price = 0;
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i] != NULL) {
            price += this->options[i]->getPrice();
        }
    }
    return price + this->model.getBaseCost();
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
    ofstream os("data/" + this->name + ".car", ios::out);
    Sanity::streamness(os, "Couldn't open " + this->name + ".car");

    StreamUtils::write(os, this->name);
    this->model.save(os);

    // Counting before because tellp/seekp didn't work D:
    int count = 0;
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) ++count;
    }
    StreamUtils::write(os, count);

    // Write  the options and count them
    for(int i = 0; i < MAX_OPTION_COUNT; ++i) {
        if(this->options[i]) {
            this->options[i]->save(os);
            ++count;
        }
    }
}

void Car::load(const String& filename) {
    Sanity::truthness(FileUtils::exists(filename), "Can't load '" + filename + "', no corresponding file");

    ifstream is(filename, ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);

    this->name = StreamUtils::readString(is);
    this->model.load(is);

    unsigned int count = StreamUtils::read<unsigned int>(is);
    for(unsigned int i = 0; i < count; ++i) {
        if(!this->options[i]) {
            this->options[i] = new Option();
        }
        this->options[i]->load(is);
    }
}

Car& Car::operator=(Car param) {
    this->name = param.name;
    this->model = param.model;
    swap(this->options, param.options);

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

int Car::compareTo(const Car& param) const {
    if(this->getPrice() == param.getPrice()) {
        return 0;
    }
    return this->getPrice() > param.getPrice() ? 1 : -1;
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
