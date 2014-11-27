#include "utils/String.hpp"

char String::END_OF_STRING = '\0';

String::String() {
    this->str = NULL;
    this->arraySize = 0;
    this->stringSize = 0;
}

String::String(char const chr, int size) {
    this->stringSize = size;
    this->reallocate(size + 1, true);
    for(int i = 0; i < size; ++i) {
        this->str[i] = chr;
    }
    this->str[size] = END_OF_STRING;
}

String::String(char const *chars) {
    this->stringSize = strlen(chars);
    this->reallocate(this->stringSize + 1, true);
    copy(this->str, chars, this->stringSize);
}

String::String(const string& str) {
    this->stringSize = str.length();
    this->reallocate(str.length() + 1, true);
    copy(this->str, str.c_str(), str.length());
}

String::String(const String& param) {
    this->stringSize = param.stringSize;
    this->reallocate(param.stringSize + 1, true);
    copy(this->str, param.str, this->stringSize);
}

String::~String() {
    if(this->str) {
        delete this->str;
    }
}

void String::reallocate(int size, bool constructing) {
    if(constructing) {
        this->str = new char[size];
        this->arraySize = size;
        return;
    }

    if(size < 0) {
        return;
    }

    if(size <= this->arraySize) {
        // Already the right size
        return;
    }

    if(size < this->stringSize) {
        // Cutting down the string, no need to reallocate
        this->stringSize = size - 1;
        this->str[size - 1] = END_OF_STRING;
        return;
    }

    if(this->str) {
        // Only dealloc and copy if there was something before
        char* tmp = this->str;
        this->str = new char[size];
        copy(this->str, tmp, size - 1);
        delete tmp;
    } else {
        this->str = new char[size];
    }

    this->arraySize = size;
}

void String::copy(char *string1, char const *string2, int end) {
    copy(string1, string2, 0, end);
}

void String::copy(char *string1, char const *string2, int start, int end) {
    for(int i = 0, j = start; j < end; ++i, ++j) {
        string1[j] = string2[i];
    }
    string1[end] = END_OF_STRING;
}

int String::length() const {
    return this->stringSize;
}

String& String::operator=(const String& param) {
    this->stringSize = param.stringSize;
    this->reallocate(this->stringSize + 1);
    copy(this->str, param.str, this->stringSize);
    return *this;
}

String& String::operator=(const char* param) {
    this->stringSize = strlen(param);
    this->reallocate(this->stringSize + 1);
    copy(this->str, param, this->stringSize);
    return *this;
}

char& String::operator[](int i) {
    if(i > this->stringSize) {
        throw new range_error("String index out of bound");
    }
    return this->str[i];
}

String String::operator+(const char *append) const {
    int totalSize = strlen(append) + this->stringSize;
    String tmp;
    tmp.reallocate(totalSize + 1);
    copy(tmp.str, this->str, this->stringSize);
    copy(tmp.str, append, this->stringSize, totalSize);
    tmp.stringSize = totalSize;

    return tmp;
}

String String::operator+(char c) const {
    String tmp(*this);
    tmp.reallocate(this->stringSize + 2);
    tmp.str[this->stringSize] = c;
    tmp.str[this->stringSize + 1] = END_OF_STRING;
    ++tmp.stringSize;
    return tmp;
}

String String::operator+(int i) const {
    stringstream s;
    s << i;

    // rely on operator+(char*)
    return *this + s.str().c_str();
}

String String::operator+(long i) const {
    stringstream s;
    s << i;

    // rely on operator+(char*)
    return *this + s.str().c_str();
}

String String::operator+(float i) const {
    stringstream s;
    s << i;

    // rely on operator+(char*)
    return *this + s.str().c_str();
}

String String::operator+(double i) const {
    stringstream s;
    s << i;

    // rely on operator+(char*)
    return *this + s.str().c_str();
}

String String::operator+(const String& param) const {
    return *this + param.str;
}

bool String::operator==(const String& param) const {
    return strcmp(this->str, param.str) == 0;
}

bool String::operator!=(const String& param) const {
    return strcmp(this->str, param.str) != 0;
}

bool String::operator>(const String& param) const {
    return strcmp(this->str, param.str) > 0;
}

bool String::operator<(const String& param) const {
    return strcmp(this->str, param.str) < 0;
}

bool String::operator>=(const String& param) const {
    return *this > param || *this == param;
}
bool String::operator<=(const String& param) const {
    return *this < param || *this == param;
}

ostream& operator<<(ostream& os, const String& str) {
    return os << (const char*) str;
}

istream& operator>>(istream& is, String& str) {
    string tmp;
    is >> tmp;
    str = tmp.c_str();
    return is;
}
