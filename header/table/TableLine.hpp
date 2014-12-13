#ifndef TABLELINE_HPP
#define TABLELINE_HPP

#include "collections/List.hpp"
#include "utils/String.hpp"

class TableLine {

private:
    List<String> columns;

public:
    TableLine(const String[], int);
    TableLine(const TableLine&);

    ConstIterator<String> iterator() const;

};

#endif
