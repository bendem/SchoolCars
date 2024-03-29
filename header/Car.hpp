#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Model.hpp"
#include "Option.hpp"
#include "exceptions/ElementNotFoundException.hpp"
#include "exceptions/IOException.hpp"
#include "exceptions/NotEnoughSpaceException.hpp"
#include "utils/ArrayUtils.hpp"
#include "utils/Comparable.hpp"
#include "utils/FileUtils.hpp"

using namespace std;

#define MAX_OPTION_COUNT 10

class Car : public Comparable<Car> {
private:
    String name;
    Model model;
    Option** options;

public:
    Car(String = "", const Model& = Model());
    Car(const Car&);
    ~Car();

    void display() const;

    void addOption(const Option&);
    void removeOption(const String&);
    Option& getOption(const String&);
    List<Option> getOptions() const;

    float getPrice() const;

    String getName() const;
    void setName(String);

    const Model& getModel() const;
    void setModel(const Model&);

    void save() const;
    void load(const String&);

    Car& operator=(Car);
    Car operator+(const Option&) const;
    Car operator-(const Option&) const;
    Car operator-(const String&) const;

    int compareTo(const Car&) const;

    friend ostream& operator<<(ostream&, const Car&);

};

#endif
