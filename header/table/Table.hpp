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
    int columnCount;
    int lines;
    int*charsInsideTheColumns; // it's an array!
    int countOfTheCharInsideTheTable;
    List<TableLine> entries;

public:
    Table(int);
    Table(const Table&);
    ~Table() { delete this->charsInsideTheColumns; }

    Table& addLine(const String[]);

    String toString() const;

    void formatTableBorder(stringstream& ss) const;

    Table& operator=(const Table&);
};

#endif
