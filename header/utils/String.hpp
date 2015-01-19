#ifndef STRING_HPP
#define STRING_HPP

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "utils/Comparable.hpp"

using namespace std;

/**
 * Represents a string holding and managing an internal char array.
 */
class String : public Comparable<String> {

private:
    static const char END_OF_STRING;

    char* str;
    unsigned int stringSize;
    unsigned int arraySize;

    /**
     * Reallocates the internal array to match the provided size.
     *
     * bool parameter is so we don't reallocate, there is not null in
     * the field but it's ok (used in constructors).
     */
    void reallocate(unsigned int, bool = false);

    /**
     * Copy a char array to another from index 0 to the provided index.
     */
    static void copy(char*, const char*, unsigned int);

    /**
     * Copy a char array to another from index the provided start to the provided end.
     *
     * bool parameter is required to be false if you don't want this method to ensure that the destination
     * ends with the string terminator character.
     */
    static void copy(char*, const char*, unsigned int, unsigned int, bool = true);

public:

    /**
     * Constructs an empty String.
     */
    String();

    /**
     * Constructs a String containing the provided char an certain amount of times.
     */
    String(const char, unsigned int);

    /**
     * Constructs a String containing the provided String an certain amount of times.
     */
    String(const String&, unsigned int);

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
    unsigned int length() const;

    /**
     * Returns wether the String is empty or not
     */
    bool isEmpty() const;

    /**
     * Transforms the String to have all its characters uppercased.
     */
    String toUpper() const;

    /**
     * Transforms the String to have all its characters lowercased.
     */
    String toLower() const;

    /**
     * Replaces the first occurence of the String with the provided replacement.
     */
    String replaceFirst(const String&, const String&) const;

    /**
     * Replaces all the occurences of the String with the provided replacement.
     */
    String replace(const String&, const String&) const;

    /**
     * Returns the index of the first occurence of the provided String in this one or -1 if not found.
     */
    int indexOf(const String&) const;

    /**
     * Parses the String and returns its integer representation on base 10.
     * @throw invalid_argument if the String does not represent a valid integer
     */
    int toInt() const;

    /**
     * Parses the String and returns its integer representation on base 10.
     * @throw invalid_argument if the String does not represent a valid integer
     */
    unsigned int toUnsignedInt() const;

    /**
     * Parses the String and returns its float representation.
     * @throw invalid_argument if the String does not represent a valid float
     */
    float toFloat() const;

    /**
     * Parses the String and returns its boolean representation.
     */
    bool toBool() const;

    // Comparisons
    int compareTo(const String&) const;

    // Appending
    String operator+(const char*) const;
    String operator+(char) const;
    String operator+(int) const;
    String operator+(long) const;
    String operator+(float) const;
    String operator+(double) const;
    String operator+(const String&) const;
    String& operator+=(const String&);

    String& operator=(String);
    String& operator=(const char*);

    char& operator[](unsigned int);

    // Casts allowing to pass String's as parameters of functions/methods using string's or char*
    operator string() const { return string(this->str); }
    operator const char*() const { return this->str; }

    template<class T>
    static String valueOf(const T&);

};

template<class T>
String String::valueOf(const T& p) { stringstream ss; ss << p; return ss.str(); }
template<>
inline String String::valueOf<bool>(const bool& b) { return b ? "true" : "false"; }

String operator+(const char*, const String&);
ostream& operator<<(ostream&, const String&);
istream& operator>>(istream&, String&);

#endif
