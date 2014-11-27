#ifndef INVALIDFUNCTIONEXCEPTION_HPP
#define INVALIDFUNCTIONEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class InvalidFunctionException : public Exception {

public:
    InvalidFunctionException() : Exception("") {}
    InvalidFunctionException(const String& message) : Exception(message, NULL) {}
    InvalidFunctionException(Exception* exception) : Exception("", exception) {}

    InvalidFunctionException(const String& message, Exception *cause) : Exception(message, cause) {}

};

#endif
