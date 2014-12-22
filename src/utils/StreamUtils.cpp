#include "utils/StreamUtils.hpp"

void StreamUtils::write(ostream& os, const String& str) {
    // Write string size
    StreamUtils::write(os, str.length());
    // Write string
    os.write(str, sizeof(char) * str.length());
}

void StreamUtils::write(ostream& os, bool b) {
    os.write((char*) &b, sizeof(bool));
}

void StreamUtils::write(ostream& os, int i) {
    os.write((char*) &i, sizeof(int));
}

void StreamUtils::write(ostream& os, unsigned int i) {
    os.write((char*) &i, sizeof(unsigned int));
}

void StreamUtils::write(ostream& os, char c) {
    os.write(&c, sizeof(char));
}

void StreamUtils::write(ostream& os, float f) {
    os.write((char*) &f, sizeof(float));
}

String StreamUtils::readString(istream& is) {
    unsigned int n = StreamUtils::read<unsigned int>(is);

    // Create a buffer of the needed size
    char buff[n+1];
    is.read(buff, n);
    buff[n] = '\0';

    return String(buff);
}

List<String> StreamUtils::readCSVLine(istream& is, int elemCount) {
    string line;
    List<String> l;
    while(--elemCount > 0) {
        getline(is, line, ';'); // Bleh :( don't like *S*tring...
        l.add(line);
    }

    getline(is, line, is.widen('\n'));
    l.add(line);

    return l;
}

void StreamUtils::skipLine(istream& is) {
    is.ignore(1000, is.widen('\n')); // Should use numeric limit, but, oh well...
}
