#ifndef NOTENOUGHSPACEEXCEPTION_HPP
#define NOTENOUGHSPACEEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class NotEnoughSpaceException : public Exception {

public:
    NotEnoughSpaceException() : Exception("") {}
    NotEnoughSpaceException(const String& message) : Exception(message, NULL) {}
    NotEnoughSpaceException(Exception* exception) : Exception("", exception) {}

    NotEnoughSpaceException(const String& message, Exception *cause) : Exception(message, cause) {}

};

#endif
