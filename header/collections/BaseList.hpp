#ifndef BASELIST_HPP
#define BASELIST_HPP

#include <iostream>

#include "utils/Predicate.hpp"
#include "utils/Sanity.hpp"

using namespace std;

template<class T>
struct Node {
    Node(const T& value, Node<T>* next) : value(value), next(next) {}
    T value;
    Node<T>* next;
};

template<class T> class BaseList;

template<class T> class ConstIterator;
template<class T> class Iterator;
#include "collections/ConstIterator.hpp"
#include "collections/Iterator.hpp"

/**
 * Base class of a linked list.
 */
template<class T>
class BaseList {

protected:
    Node<T>* first;
    unsigned int nbElems;

public:
    BaseList();
    BaseList(const BaseList<T>&);
    virtual ~BaseList();

    /**
     * Returns wether the list contains items or not.
     */
    bool isEmpty() const;

    /**
     * Returns the current size of the list.
     */
    unsigned int size() const;

    /**
     * Removes the item at the provided position.
     */
    void remove(unsigned int);

    /**
     * Removes all items from the list.
     */
    void clear();

    /**
     * Adds all the items contained in the list passed as parameter.
     */
    void addAll(const BaseList&);

    /**
     * Adds an element to the list.
     */
    virtual void add(const T&) = 0;

    /**
     * Checks wether the list contains the provided element or not.
     */
    //virtual bool contains(const T&) const;

    /**
     * Checks wether the list contains an element matching the provided predicate.
     */
    bool containsWithPredicate(const Predicate<T>&) const;

    BaseList<T>& operator=(const BaseList<T>&);

    // Eww (Horrible, has nothing to do in a list class) :(
    //void display() const;

    friend class ConstIterator<T>;
    friend class Iterator<T>;

};

#endif
