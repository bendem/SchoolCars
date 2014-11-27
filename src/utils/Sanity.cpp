#include "utils/Sanity.hpp"

void Sanity::truthness(bool cond, String error) {
    if(!cond) {
        throw AssertionException(error);
    }
}

void Sanity::nullness(void* ptr, String error) {
    if(ptr == NULL) {
        throw AssertionException(error);
    }
}
