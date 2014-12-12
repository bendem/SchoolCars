#ifndef SORTEDLIST_HPP
#define SORTEDLIST_HPP

#include "collections/List.hpp"

/**
 * Represents a list sorted based on its item comparison.
 */
template<class T>
class SortedList : public List<T> {

public:

    /**
     * Adds the element in the list so that all elements keeps their order.
     */
    void add(const T&);

    /**
     * Checks wether the provided object is contained in the list.
     */
    bool contains(const T&) const;

};

#endif
