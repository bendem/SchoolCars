#ifndef STRING_HPP
#define STRING_HPP

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

class String {

private:
    static char END_OF_STRING;

    char* str;
    int stringSize;
    int arraySize;
    void reallocate(int, bool = false); // bool is so we don't reallocate, there is not null in the field but it's ok (used in constructors)
    static void copy(char*, const char*, int);
    static void copy(char*, const char*, int, int);

public:
    String();
    String(const char, int);
    String(const String&, int);
    String(const char*);
    String(const string&);
    String(const String&);
    ~String();

    int length() const;
    void toUpper();
    void toLower();

    String& operator=(const String&);
    String& operator=(const char*);

    char& operator[](int);

    // Casts
    operator string() const { return string(this->str); }
    operator const char*() const { return this->str; }
    int toInt() const;
    float toFloat() const;
    bool toBool() const;

    // Appending
    String operator+(const char*) const;
    String operator+(char) const;
    String operator+(int) const;
    String operator+(long) const;
    String operator+(float) const;
    String operator+(double) const;
    String operator+(const String&) const;

    // Comparisons
    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    bool operator>(const String&) const;
    bool operator<(const String&) const;
    bool operator>=(const String&) const;
    bool operator<=(const String&) const;

};

ostream& operator<<(ostream&, const String&);
istream& operator>>(istream&, String&);

#endif
