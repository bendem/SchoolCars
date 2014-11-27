#ifndef ELEMENTNOTFOUNDEXCEPTION_HPP
#define ELEMENTNOTFOUNDEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class ElementNotFoundException : public Exception {

public:
    ElementNotFoundException() : Exception("") {}
    ElementNotFoundException(const String& message) : Exception(message, NULL) {}
    ElementNotFoundException(Exception* exception) : Exception("", exception) {}

    ElementNotFoundException(const String& message, Exception *cause) : Exception(message, cause) {}

};

#endif
