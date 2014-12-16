#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "exceptions/Exception.hpp"

class IOException : public Exception {

public:
    IOException() : Exception("") {}
    IOException(const String& message) : Exception(message) {}

};

#endif
