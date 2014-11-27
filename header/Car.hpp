#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>

#include "exceptions/ElementNotFoundException.hpp"
#include "exceptions/NotEnoughSpaceException.hpp"
#include "Model.hpp"
#include "Option.hpp"

using namespace std;

#define MAX_OPTION_COUNT 10

class Car {
private:
    String name;
    Model model;
    Option *options[MAX_OPTION_COUNT];

public:
    Car(String = "", Model = Model());
    Car(const Car&);

    void display() const;

    void addOption(const Option&);
    void removeOption(const String&);

    float getPrice() const;

    String getName() const;
    void setName(String);

    const Model& getModel() const;
    void setModel(const Model&);

    void save() const;
    void load(const String&);

    Car& operator=(const Car&);
    Car operator+(const Option&) const;
    Car operator-(const Option&) const;
    Car operator-(const String&) const;
    bool operator>(const Car&);
    bool operator<(const Car&);
    bool operator==(const Car&);
    friend ostream& operator<<(ostream&, const Car&);
    friend istream& operator>>(istream&, Car&);

};

#endif
