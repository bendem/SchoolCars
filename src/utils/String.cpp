#include "utils/String.hpp"

const char String::END_OF_STRING = '\0';

String::String() {
    this->str = NULL;
    this->arraySize = 0;
    this->stringSize = 0;
}

String::String(char const chr, int size) {
    if(size == 0) {
        this->str = NULL;
        this->arraySize = 0;
        this->stringSize = 0;
        return;
    }

    this->stringSize = size;
    this->reallocate(size + 1, true);
    for(int i = 0; i < size; ++i) {
        this->str[i] = chr;
    }
    this->str[size] = END_OF_STRING;
}

String::String(const String& str, int size) {
    if(str.length() == 0) {
        this->str = NULL;
        this->arraySize = 0;
        this->stringSize = 0;
        return;
    }

    this->stringSize = size * str.length();
    this->reallocate(this->stringSize + 1, true);
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < str.length(); ++j) {
            this->str[i * str.length() + j] = str[j];
        }
    }
    this->str[this->stringSize] = END_OF_STRING;
}

String::String(char const *chars) {
    this->stringSize = strlen(chars);

    if(this->stringSize == 0) {
        this->str = NULL;
        this->arraySize = 0;
        return;
    }

    this->reallocate(this->stringSize + 1, true);
    copy(this->str, chars, this->stringSize);
}

String::String(const string& str) {
    if(str.length() == 0) {
        this->str = NULL;
        this->arraySize = 0;
        this->stringSize = 0;
        return;
    }

    this->stringSize = str.length();
    this->reallocate(str.length() + 1, true);
    copy(this->str, str.c_str(), str.length());
}

String::String(const String& param) {
    if(param.stringSize == 0) {
        this->str = NULL;
        this->stringSize = 0;
        this->arraySize = 0;
        return;
    }

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
        /* If we are currently constructing the char array,
         * we bypass all checks and just allocate the array */
        this->str = new char[size];
        this->arraySize = size;
        return;
    }

    if(size < 0) {
        // Invalid size, ignoring
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

void String::copy(char* dest, const char* source, int end) {
    copy(dest, source, 0, end);
}

void String::copy(char* dest, const char* source, int start, int end, bool ensureEOS) {
    for(int i = 0, j = start; j < end; ++i, ++j) {
        dest[j] = source[i];
    }
    if(ensureEOS) {
        dest[end] = END_OF_STRING;
    }
}

int String::length() const {
    return this->stringSize;
}
void String::toUpper() {
    for(int i = 0; i < this->stringSize; ++i) {
        this->str[i] = toupper(this->str[i]);
    }
}

void String::toLower() {
    for(int i = 0; i < this->stringSize; ++i) {
        this->str[i] = tolower(this->str[i]);
    }
}

String& String::replace(const String& search, const String& replace) {
    if(search.length() == 0) {
        return *this;
    }

    int index;
    int addedSize = replace.length() - search.length();

    while((index = this->indexOf(search)) != -1) {
        this->stringSize += addedSize;
        if(addedSize > 0) {
            // Move towards the end
            // Reallocate if needed
            if(this->stringSize + addedSize > this->arraySize) {
                this->reallocate(this->stringSize + addedSize);
            }
            // Backward copy preventing from overriding what is being written
            for(int i = this->stringSize - 1; i >= index + search.length(); --i) {
                this->str[i + addedSize] = this->str[i];
            }
        } else if(addedSize < 0) {
            // Move forward
            for(int i = index + replace.length(); i < this->stringSize + addedSize; ++i) {
                this->str[i] = this->str[i - addedSize];
            }
            this->str[this->stringSize + addedSize] = END_OF_STRING;
        }

        copy(this->str, replace, index, index + replace.length(), false);
    }
    return *this;
}

int String::indexOf(const String& search) const {
    int found = 0;
    int index;
    for(int i = 0; i < this->stringSize; ++i) {
        if(this->str[i] == search[found]) {
            if(found == 0) {
                index = i;
            }
            ++found;
            if(found == search.length()) {
                return index;
            }
        } else {
            found = 0;
        }
    }
    return -1;
}

String& String::operator=(String param) {
    swap(this->stringSize, param.stringSize);
    swap(this->arraySize, param.arraySize);
    swap(this->str, param.str);
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

int String::toInt() const {
    if(this->length() == 0) {
        throw invalid_argument("empty string");
    }

    bool negate = this->str[0] == '-';
    char* s = this->str;

    if(*s == '+' || *s == '-') {
        ++s;
    }

    if(*s == '\0') {
        throw invalid_argument("sign character only");
    }

    int result = 0;
    while(*s) {
        if(*s < '0' || *s > '9') {
            throw invalid_argument("the String is not an integer");
        }
        result = result * 10  + (*s - '0');
        ++s;
    }
    return negate ? -result : result;
}

float String::toFloat() const {
    if(this->length() == 0) {
        throw invalid_argument("empty String");
    }

    float result = 0;
    bool dec = false;
    int decCount = 0;
    bool niggative = this->str[0] == '-';
    char* s = this->str;

    if(*s == '+' || *s == '-') {
        ++s;
    }

    if(*s == '\0') {
        throw invalid_argument("sign character only");
    }

    while(*s) {
        if(*s == '.') {
            if(dec) {
                throw invalid_argument("multiple points");
            }
            dec = true;
            ++s;
            continue;
        }

        if(*s < '0' || *s > '9') {
            throw invalid_argument("the String is not an integer");
        }

        if(dec) {
            ++decCount;
        }
        result = result * 10  + (*s - '0');
        ++s;
    }

    if(niggative) {
        result = -result;
    }

    if(decCount == 0) {
        return result;
    }

    return result / pow((double) 10, (double) decCount);
}

bool String::toBool() const {
    String tmp(*this);
    tmp.toLower();
    return tmp != (String) "false"
        && tmp != (String) "faux"
        && tmp != (String) "0"
        && tmp != (String) "n"
        && tmp != (String) "no"
        && tmp != (String) "non"
        && tmp != (String) "nein"
        && tmp != (String) "wrong"
        ;
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

int String::compareTo(const String& param) const {
    return strcmp(this->str, param.str);
}

ostream& operator<<(ostream& os, const String& str) {
    if(str.length() > 0) {
        os << (const char*) str;
    }
    return os;
}

istream& operator>>(istream& is, String& str) {
    string tmp;
    getline(is, tmp);
    str = tmp.c_str();
    return is;
}
