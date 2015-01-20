#include "exceptions/Exception.hpp"

Exception::Exception(const String& message) {
    this->message = message;
}

Exception::Exception(const Exception& param) : exception() {
    this-> message = param.message;
}

const char* Exception::what() const throw() {
    return this->message;
}

void Exception::display() const {
    cout << "Exception: " << this->message << endl;
}
