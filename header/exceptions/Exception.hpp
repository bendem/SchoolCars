#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <iostream>

#include "utils/String.hpp"

using namespace std;

class Exception : public exception {

protected:
    String message;

public:
    Exception(const String& = "");
    Exception(const Exception&);
    ~Exception() throw() {}

    const char* what() const throw();
    virtual void display() const;

};

#endif
