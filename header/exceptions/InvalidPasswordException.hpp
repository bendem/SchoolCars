#ifndef INVALIDPASSWORDEXCEPTION_HPP
#define INVALIDPASSWORDEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class InvalidPasswordException : public Exception {

public:
    InvalidPasswordException() : Exception("") {}
    InvalidPasswordException(const String& message) : Exception(message) {}

};

#endif
