#ifndef LIST_HPP
#define LIST_HPP

#include "collections/BaseList.hpp"
#include "collections/Iterator.hpp"
#include "utils/Optional.hpp"
#include "utils/Predicate.hpp"
#include "utils/Sanity.hpp"

template<class E> class ListIterator;
template<class E> class ConstListIterator;

/**
 * Represents a classic list sorted by insertion order.
 */
template<class T>
class List : public BaseList<T> {

public:

    /**
     * Adds the provided element to the end of the list.
     */
    void add(const T&);

    /**
     * Returns the element at the provided index in the list
     */
    T get(int) const;

    /**
     * Returns an optional value continaing the first element of the list
     * matching the provided predicate.
     */
    Optional<T> getFirstMatching(const Predicate<T>&);

};

#endif
