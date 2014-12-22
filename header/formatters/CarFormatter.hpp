#ifndef CARFORMATTER_HPP
#define CARFORMATTER_HPP

#include "Car.hpp"
#include "utils/Formatter.hpp"

class CarFormatter : public Formatter<Car> {

public:
    CarFormatter(Car const& p) : Formatter(p) {}
    String format(int) const;

};

#endif
