#include "table/Table.hpp"

Table::Table(int width, int maxTableWidth) {
    this->lines = 0;
    this->width = width;
    this->charsInsideTheColumns = new int[width];
    ArrayUtils::fill<int>(this->charsInsideTheColumns, 0, width);
    this->countOfTheCharInsideTheTable = 0;
    this->maxTableWidth = maxTableWidth;
}

Table::Table(const Table& param) {
    this->lines = param.lines;
    this->width = param.width;
    this->charsInsideTheColumns = new int[this->width];
    ArrayUtils::copy<int>(this->charsInsideTheColumns, param.charsInsideTheColumns, this->width);
    this->maxTableWidth = param.maxTableWidth;
}

Table& Table::addLine(const String columns[]) {
    TableLine t(columns, this->width);
    this->entries.add(t);

    for(int i = 0; i < this->width; ++i) {
        if(this->charsInsideTheColumns[i] < columns[i].length()) {
            this->countOfTheCharInsideTheTable += columns[i].length() - this->charsInsideTheColumns[i];
            this->charsInsideTheColumns[i] = columns[i].length();
        }
    }

    return *this;
}

String Table::toString() const {
    int tableWidth = this->countOfTheCharInsideTheTable + 3 * (this->width - 1) + 4;
    if(tableWidth > this->maxTableWidth) {
        // TODO Handle line wrapping somehow
        return "error";
    }

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
    for(int i = 0; i < width; ++i) {
        ss << String('-', charsInsideTheColumns[i]+2) << "+";
    }
    ss << endl;
}

Table& Table::operator=(const Table&) {
    return *this;
}
