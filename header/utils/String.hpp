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

/**
 * Represents a string holding and managing an internal char array.
 */
class String {

private:
    static const char END_OF_STRING;

    char* str;
    int stringSize;
    int arraySize;

    /**
     * Reallocates the internal array to match the provided size.
     *
     * bool parameter is so we don't reallocate, there is not null in
     * the field but it's ok (used in constructors).
     */
    void reallocate(int, bool = false);

    /**
     * Copy a char array to another from index 0 to the provided index.
     */
    static void copy(char*, const char*, int);

    /**
     * Copy a char array to another from index the provided start to the provided end.
     */
    static void copy(char*, const char*, int, int);

public:

    /**
     * Constructs an empty String.
     */
    String();

    /**
     * Constructs a String containing the provided char an certain amount of times.
     */
    String(const char, int);

    /**
     * Constructs a String containing the provided String an certain amount of times.
     */
    String(const String&, int);

    /**
     * Constructs a String based on the provided C char* (allows to use char*
     * as parameters of methods taking String's).
     */
    String(const char*);

    /**
     * Constructs a String based on the provided C++ string (allows to use string's
     * as parameters of methods taking String's).
     */
    String(const string&);
    String(const String&);
    ~String();

    /**
     * Returns the length of the String.
     */
    int length() const;

    /**
     * Transforms the String to have all its characters uppercased.
     */
    void toUpper();

    /**
     * Transforms the String to have all its characters lowercased.
     */
    void toLower();

    String& operator=(const String&);
    String& operator=(const char*);

    char& operator[](int);

    // Casts allowing to pass String's as parameters of functions/methods using string's or char*
    operator string() const { return string(this->str); }
    operator const char*() const { return this->str; }

    /**
     * Parses the String and returns its integer representation on base 10.
     * @throw invalid_argument if the String does not represent a valid integer
     */
    int toInt() const;

    /**
     * Parses the String and returns its float representation.
     * @throw invalid_argument if the String does not represent a valid float
     */
    float toFloat() const;

    /**
     * Parses the String and returns its boolean representation.
     */
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
