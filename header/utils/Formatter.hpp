#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "utils/String.hpp"

template<class T>
class Formatter {

protected:
    const T& obj;

public:
    Formatter(const T& p) : obj(p) {}
    virtual String format(unsigned int indent) const = 0;

};

#endif
