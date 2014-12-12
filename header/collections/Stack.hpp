#ifndef STACK_HPP
#define STACK_HPP

#include "collections/BaseList.hpp"
#include "collections/List.hpp"

/**
 * Stack implementation based on a linked list.
 */
template<class T>
class Stack : public BaseList<T> {

public:

    /**
     * Adds the provided element at the start of the list.
     */
    void add(T const& param);

    /**
     * Returns the element at the start of the list and removes it from it.
     *
     * @throw AssertionException if there is no element in the list.
     */
    T pop();

};

#endif
