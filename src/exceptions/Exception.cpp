#include "exceptions/Exception.hpp"

Exception::Exception(const String& message, Exception *exception) {
    this->message = message;
    this->cause = exception;
}

Exception::Exception(const Exception& param) {
    this-> message = param.message;
    if(param.cause) {
        this->cause = new Exception(*param.cause);
    } else {
        this->cause = NULL;
    }
}

Exception::~Exception() {
    if(this->cause) {
        delete this->cause;
    }
}

String Exception::getMessage() const {
    return this->message;
}

const Exception& Exception::getCause() const {
    return *this->cause;
}

void Exception::display() const {
    cout << "Exception: " << this->message << endl;
    const Exception *cause = this->cause;
    while(cause != NULL) {
        cout << "Caused by" << cause->message << endl;
        cause = cause->cause;
    }
}
