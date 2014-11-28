#include "utils/FileUtils.hpp"

bool FileUtils::exists(const String& filename) {
    ifstream is(filename, ios::in);
    return is.good();
}
