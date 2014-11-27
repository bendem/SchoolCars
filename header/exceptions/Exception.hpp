#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include "utils/String.hpp"

using namespace std;

class Exception {
protected:
    String message;
    const Exception* cause;
public:
    Exception(const String& = "", Exception* = NULL);
    Exception(const Exception&);
    virtual ~Exception();

    String getMessage() const;
    const Exception& getCause() const;
    virtual void display() const;

};

#endif
