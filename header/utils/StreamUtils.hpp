#ifndef STREAMUTILS_HPP
#define STREAMUTILS_HPP

#include <iostream>

#include "collections/List.hpp"
#include "collections/SortedList.hpp"
#include "utils/String.hpp"

using namespace std;

/**
 * Easy to use utility to write and read primitive types in and out of streams.
 */
class StreamUtils {

private:
    template<class T>
    static void readAllTheLists(List<T>& list, istream& is) { // YOU BROKE IT SOMEWHERE WITH THESE PURE CALLS
        unsigned int count = StreamUtils::read<unsigned int>(is);
        for(unsigned int i = 0; i < count; ++i) {
            list.add(StreamUtils::readObject<T>(is));
        }
    }

public:

    // Binary write operations
    static void write(ostream&, const String&);
    static void write(ostream&, bool);
    static void write(ostream&, int);
    static void write(ostream&, unsigned int);
    static void write(ostream&, char);
    static void write(ostream&, float);

    template<class T>
    static void writeObject(ostream& os, const T& obj) { obj.save(os); }

    template<class T>
    static void writeList(ostream& os, const List<T>& list) {
        StreamUtils::write(os, list.size());
        ConstIterator<T> it(list);
        while(!it.end()) {
            StreamUtils::writeObject(os, it++.get());
        }
    }

    // Binary read operations
    static String readString(istream&);

    template<class T>
    static T read(istream& is) {
        T var;
        is.read((char*) &var, sizeof(T));
        return var;
    }

    template<class T>
    static T readObject(istream& is) {
        T obj;
        obj.load(is);
        return obj;
    }

    template<class T>
    static List<T> readList(istream& is) {
        List<T> list;
        readAllTheLists(list, is);
        return list;
    }
    template<class T>
    static SortedList<T> readSortedList(istream& is) {
        SortedList<T> list;
        readAllTheLists(list, is);
        return list;
    }

    // CSV operations
    /**
     * Returns a list of string containing the elements of a single line read in a csv file.
     */
    static List<String> readCSVLine(istream&, int);

    /**
     * Skips a line on a character based input stream.
     */
    static void skipLine(istream&);

};

#endif
