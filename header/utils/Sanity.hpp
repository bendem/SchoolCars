#ifndef SANITY_HPP
#define SANITY_HPP

#include "exceptions/AssertionException.hpp"

using namespace std;

class Sanity {

public:
    static void truthness(bool cond, const String& error);
    static void nullness(const void* cond, const String& error);

};

#endif
