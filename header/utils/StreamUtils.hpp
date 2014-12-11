#ifndef STREAMUTILS_HPP
#define STREAMUTILS_HPP

#include <ctime>
#include <iostream>
#include "collections/List.hpp"
#include "utils/String.hpp"

using namespace std;

class StreamUtils {

public:
    static void write(ostream&, const String&);
    static void write(ostream&, bool);
    static void write(ostream&, int);
    static void write(ostream&, char);
    static void write(ostream&, float);

    static String readString(istream&);
    static bool   readBool(istream&);
    static int    readInt(istream&);
    static char   readChar(istream&);
    static float  readFloat(istream&);

    static List<String> readCSVLine(istream&, int);
    static void skipLine(istream&);

};

#endif
