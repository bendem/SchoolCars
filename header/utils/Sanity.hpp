#ifndef SANITY_HPP
#define SANITY_HPP

#include "exceptions/AssertionException.hpp"

using namespace std;

class Sanity {

public:
    static void truthness(bool cond, String error);
    static void nullness(void* cond, String error);

};

#endif
