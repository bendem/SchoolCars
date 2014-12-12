#include "utils/Sanity.hpp"

void Sanity::truthness(bool cond, const String& error) {
    if(!cond) {
        throw AssertionException(error);
    }
}

void Sanity::nullness(const void* ptr, const String& error) {
    if(ptr == NULL) {
        throw AssertionException(error);
    }
}
