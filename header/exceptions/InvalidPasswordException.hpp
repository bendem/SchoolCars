#ifndef INVALIDPASSWORDEXCEPTION_HPP
#define INVALIDPASSWORDEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class InvalidPasswordException : public Exception {

public:
    InvalidPasswordException() : Exception("") {}
    InvalidPasswordException(const String& message) : Exception(message, NULL) {}
    InvalidPasswordException(Exception* exception) : Exception("", exception) {}

    InvalidPasswordException(const String& message, Exception *cause) : Exception(message, cause) {}

};

#endif
