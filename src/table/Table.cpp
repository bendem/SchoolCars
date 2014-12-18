#include "table/Table.hpp"

Table::Table(int columnCount) {
    this->headers = NULL;
    this->columnCount = columnCount;
    this->charsInsideTheColumns = new int[columnCount];
    ArrayUtils::fill<int>(this->charsInsideTheColumns, 0, columnCount);
    this->countOfTheCharInsideTheTable = 0;
}

Table::Table(const Table& param) {
    this->columnCount = param.columnCount;
    this->countOfTheCharInsideTheTable = param.countOfTheCharInsideTheTable;
    this->entries = param.entries; // maybe redirect instead?

    this->headers = new String[this->columnCount];
    ArrayUtils::copy<String>(this->headers, param.headers, this->columnCount);

    this->charsInsideTheColumns = new int[this->columnCount];
    ArrayUtils::copy<int>(this->charsInsideTheColumns, param.charsInsideTheColumns, this->columnCount);
}

Table::~Table() {
    delete this->charsInsideTheColumns;
    if(this->headers) {
        delete[] this->headers;
    }
}

void Table::checkMaxLengths(const String array[]) {
    for(int i = 0; i < this->columnCount; ++i) {
        if(this->charsInsideTheColumns[i] < array[i].length()) {
            this->countOfTheCharInsideTheTable += array[i].length() - this->charsInsideTheColumns[i];
            this->charsInsideTheColumns[i] = array[i].length();
        }
    }
}

void Table::formatTableBorder(stringstream& ss) const {
    ss << " +";
    for(int i = 0; i < this->columnCount; ++i) {
        ss << String('-', this->charsInsideTheColumns[i]+2) << "+";
    }
    ss << endl;
}

void Table::formatHeader(stringstream& ss) const {
    ss << " | ";
    for(int i = 0; i < this->columnCount; ++i) {
        ss
            << this->headers[i]
            << String(' ', this->charsInsideTheColumns[i] - this->headers[i].length())
            << " |";
        if(i + 1 != this->columnCount) {
            ss << ' ';
        }
    }
    ss << endl;
}

Table& Table::setHeader(const String headers[]) {
    this->headers = new String[this->columnCount];
    ArrayUtils::copy<String>(this->headers, headers, this->columnCount);

    this->checkMaxLengths(headers);

    return *this;
}

Table& Table::addLine(const String columns[]) {
    TableLine t(columns, this->columnCount);
    this->entries.add(t);

    this->checkMaxLengths(columns);

    return *this;
}

void Table::clear() {
    ArrayUtils::fill<int>(this->charsInsideTheColumns, 0, columnCount);
    this->countOfTheCharInsideTheTable = 0;
    this->entries.clear();
}

String Table::toString() const {
    stringstream ss;
    this->formatTableBorder(ss);
    if(this->headers) {
        this->formatHeader(ss);
        this->formatTableBorder(ss);
    }

    ConstIterator<TableLine> lineIterator(this->entries);
    while(!lineIterator.end()) {

        ss << " | ";
        int i = 0;
        ConstIterator<String> it((&lineIterator).iterator());
        while(!it.end()) {
            ss << it;
            ss << String(' ', this->charsInsideTheColumns[i] - (&it).length()); // Fills the end of the column
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

Table& Table::operator=(Table param) {
    swap(this->headers, param.headers);
    swap(this->columnCount, param.columnCount);
    swap(this->charsInsideTheColumns, param.charsInsideTheColumns);
    swap(this->countOfTheCharInsideTheTable, param.countOfTheCharInsideTheTable);
    swap(this->entries, param.entries);

    return *this;
}
