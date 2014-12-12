#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <fstream>

#include "utils/String.hpp"

using namespace std;

class FileUtils {

public:

    /**
     * Checks wether a file exists at the provided path.
     */
    static bool exists(const String&);

};

#endif
