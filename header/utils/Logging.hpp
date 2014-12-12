#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <ctime>

#include "utils/String.hpp"

/**
 * Returns a conveniently formated String containing the time and the provided String on the form of "[time] [string]".
 * (Very useful for logs :3)
 */
String time(const String&);

#endif
