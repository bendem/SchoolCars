#ifndef NOTENOUGHSPACEEXCEPTION_HPP
#define NOTENOUGHSPACEEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class NotEnoughSpaceException : public Exception {

public:
    NotEnoughSpaceException() : Exception("") {}
    NotEnoughSpaceException(const String& message) : Exception(message) {}

};

#endif
