#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "collections/BaseList.hpp"

/**
 * Structure allowing to iterate through a BaseList instance.
 *
 * Example usage:
 * ```C++
 * Iterator<Type> iterator(list);
 * while(!it.end()) {
 *     doStuff((Type) it);
 *     ++it;
 * }
 * ```
 *
 * You can get the reference of the object currently pointed by the iterator
 * by using ``(&iterator).method()``.
 */
template<class T>
class Iterator {

private:
    BaseList<T>& list;
    Node<T>* current;
    Node<T>* prec;

public:
    Iterator(BaseList<T>&);
    Iterator(const Iterator<T>&);
    ~Iterator();

    /**
     * Checks wether the iterator is pointing at the end of the list.
     *
     * If this returns true, the currently selected element is null!
     */
    bool end();

    /**
     * Resets the position of the iterator in the list to the first element.
     */
    void reset();

    /**
     * Removes the element currently pointed by the iterator from the list.
     */
    T remove();
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    operator T();
    T& operator &();

    Iterator<T>& operator=(const Iterator<T>&);

};

#endif
