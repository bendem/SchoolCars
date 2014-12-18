#ifndef TABLE_HPP
#define TABLE_HPP

#include <sstream>

#include "collections/List.hpp"
#include "table/TableLine.hpp"
#include "utils/ArrayUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Table {

private:
    String* headers;
    int columnCount;
    int* charsInsideTheColumns; // it's an array!
    int countOfTheCharInsideTheTable;
    List<TableLine> entries;

    void checkMaxLengths(const String[]);
    void formatHeader(stringstream&) const;
    void formatTableBorder(stringstream& ss) const;

public:
    Table(int);
    Table(const Table&);
    ~Table();

    Table& setHeader(const String[]);
    Table& addLine(const String[]);
    void clear();

    String toString() const;

    Table& operator=(Table);

};

#endif
