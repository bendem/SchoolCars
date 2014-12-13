#include "table/Table.hpp"

Table::Table(int columnCount) {
    this->lines = 0;
    this->columnCount = columnCount;
    this->charsInsideTheColumns = new int[columnCount];
    ArrayUtils::fill<int>(this->charsInsideTheColumns, 0, columnCount);
    this->countOfTheCharInsideTheTable = 0;
}

Table::Table(const Table& param) {
    this->lines = param.lines;
    this->columnCount = param.columnCount;
    this->charsInsideTheColumns = new int[this->columnCount];
    ArrayUtils::copy<int>(this->charsInsideTheColumns, param.charsInsideTheColumns, this->columnCount);
}

Table& Table::addLine(const String columns[]) {
    TableLine t(columns, this->columnCount);
    this->entries.add(t);

    for(int i = 0; i < this->columnCount; ++i) {
        if(this->charsInsideTheColumns[i] < columns[i].length()) {
            this->countOfTheCharInsideTheTable += columns[i].length() - this->charsInsideTheColumns[i];
            this->charsInsideTheColumns[i] = columns[i].length();
        }
    }

    return *this;
}

String Table::toString() const {
    int tableWidth = this->countOfTheCharInsideTheTable + 3 * (this->columnCount - 1) + 4;

    stringstream ss;
    this->formatTableBorder(ss);

    ConstIterator<TableLine> lineIterator(this->entries);
    while(!lineIterator.end()) {

        ss << " | ";
        int i = 0;
        ConstIterator<String> it((&lineIterator).iterator());
        while(!it.end()) {
            ss << it;
            ss << String(' ', this->charsInsideTheColumns[i] - (&it).length());// Fills the end of the column
            ss << " |";
            ++it;
            ++i;
            if(!it.end()) {
                ss << ' ';
            }
        }
        ss << endl;

        ++lineIterator;
    }

    this->formatTableBorder(ss);
    return ss.str();
}

void Table::formatTableBorder(stringstream& ss) const {
    ss << " +";
    for(int i = 0; i < columnCount; ++i) {
        ss << String('-', charsInsideTheColumns[i]+2) << "+";
    }
    ss << endl;
}

Table& Table::operator=(const Table&) {
    return *this;
}
