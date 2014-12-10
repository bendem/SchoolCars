#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <iostream>

using namespace std;

template<class T>
class Optional {

private:
    T* value;

public:
    Optional() : value(NULL) {}
    Optional(T *value) : value(value) {}
    Optional(const Optional<T>& param) : value(param.value) {}
    ~Optional() {}

    bool hasValue() const { return this->value != NULL; }
    T& get() { return *this->value; }

    Optional<T>& operator=(const Optional<T> param) { this->value = param.value; }

};

#endif
