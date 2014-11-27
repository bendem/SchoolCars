#include "utils/StreamUtils.hpp"

void StreamUtils::write(ostream& os, const String& str) {
    // Write string size
    int n = str.length();
    os.write((char*) &n, sizeof(int));
    // Write string
    os.write(str, sizeof(char) * n);
}

void StreamUtils::write(ostream& os, bool b) {
    os.write((char*) &b, sizeof(bool));
}

void StreamUtils::write(ostream& os, int i) {
    os.write((char*) &i, sizeof(int));
}

void StreamUtils::write(ostream& os, char c) {
    os.write(&c, sizeof(char));
}

void StreamUtils::write(ostream& os, float f) {
    os.write((char*) &f, sizeof(float));
}

String StreamUtils::readString(istream& is) {
    int n;
    // Read string size
    is.read((char*) &n, sizeof(int));

    // Create a buffer of the needed size
    char buff[n];
    is.read(buff, n);
    buff[n] = '\0';

    return String(buff);
}

bool StreamUtils::readBool(istream& is) {
    bool b;
    is.read((char*) &b, sizeof(bool));
    return b;
}

int StreamUtils::readInt(istream& is) {
    int i;
    is.read((char*) &i, sizeof(int));
    return i;
}

char StreamUtils::readChar(istream& is) {
    char c;
    is.read(&c, sizeof(char));
    return c;
}

float StreamUtils::readFloat(istream& is) {
    float f;
    is.read((char*) &f, sizeof(int));
    return f;
}
