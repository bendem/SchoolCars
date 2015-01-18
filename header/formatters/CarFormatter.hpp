#ifndef CARFORMATTER_HPP
#define CARFORMATTER_HPP

#include "Car.hpp"
#include "formatters/CarFormatter.hpp"
#include "utils/Formatter.hpp"
#include "utils/TermUtils.hpp"

class CarFormatter : public Formatter<Car> {

public:
    CarFormatter(Car const& p) : Formatter(p) {}
    String format(unsigned int) const;

};

#endif
