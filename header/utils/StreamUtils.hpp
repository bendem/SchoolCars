#ifndef STREAMUTILS_HPP
#define STREAMUTILS_HPP

#include <ctime>
#include <iostream>
#include "collections/List.hpp"
#include "utils/String.hpp"

using namespace std;

/**
 * Easy to use utility to write and read primitive types in and out of streams.
 */
class StreamUtils {

public:
    static void write(ostream&, const String&);
    static void write(ostream&, bool);
    static void write(ostream&, int);
    static void write(ostream&, unsigned int);
    static void write(ostream&, char);
    static void write(ostream&, float);

    static String readString(istream&);

    template<class T>
    static T read(istream& is) {
        T var;
        is.read((char*) &var, sizeof(T));
        return var;
    }

    /**
     * Returns a list of string containing the elements of a single line read in a csv file.
     */
    static List<String> readCSVLine(istream&, int);

    /**
     * Skips a line on a character based input stream.
     */
    static void skipLine(istream&);

};

#endif
