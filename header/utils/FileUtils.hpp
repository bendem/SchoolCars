#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <fstream>

#include "utils/String.hpp"

using namespace std;

class FileUtils {

public:
    static bool exists(const String&);

};

#endif
