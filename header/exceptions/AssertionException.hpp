#ifndef ASSERTIONEXCEPTION_HPP
#define ASSERTIONEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class AssertionException : public Exception {

public:
    AssertionException() : Exception("") {}
    AssertionException(const String& message) : Exception(message, NULL) {}
    AssertionException(Exception* exception) : Exception("", exception) {}

    AssertionException(const String& message, Exception *cause) : Exception(message, cause) {}

};

#endif
