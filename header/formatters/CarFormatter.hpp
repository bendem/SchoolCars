#ifndef CARFORMATTER_HPP
#define CARFORMATTER_HPP

#include "Car.hpp"
#include "utils/Formatter.hpp"
#include "utils/String.hpp"

class CarFormatter : public Formatter<Car> {

public:
    CarFormatter(Car const& p) : Formatter(p) {}
    String format() const;

};

#endif
