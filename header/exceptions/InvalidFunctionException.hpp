#ifndef INVALIDFUNCTIONEXCEPTION_HPP
#define INVALIDFUNCTIONEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class InvalidFunctionException : public Exception {

public:
    InvalidFunctionException() : Exception("") {}
    InvalidFunctionException(const String& message) : Exception(message) {}

};

#endif
