#ifndef SORTEDLIST_HPP
#define SORTEDLIST_HPP

#include "collections/List.hpp"

template<class T>
class SortedList : public List<T> {

public:
    void add(const T&);

};

#endif
