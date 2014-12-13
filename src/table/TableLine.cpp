#include "table/TableLine.hpp"

TableLine::TableLine(const String param[], int size) {
    for(int i = 0; i < size; ++i) {
        this->columns.add(param[i]);
    }
}

TableLine::TableLine(const TableLine& param) {
    this->columns = param.columns;
}

ConstIterator<String> TableLine::iterator() const {
    return ConstIterator<String>(this->columns);
}

