#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "utils/String.hpp"

template<class T>
class Formatter {

protected:
    const T& obj;

public:
    Formatter(const T& p) : obj(p) {}
    virtual String format() const = 0;

};

template<class T>
ostream& operator<<(ostream& os, const Formatter<T>& formatter) {
    return os << formatter.format();
}

#endif
