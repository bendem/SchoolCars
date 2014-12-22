#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "BaseList.hpp"

/**
 * Structure allowing to iterate through a constant BaseList instance.
 *
 * Example usage:
 * ```C++
 * ConstIterator<Type> iterator(list);
 * while(!it.end()) {
 *     doStuff((Type) it);
 *     ++it;
 * }
 * ```
 */
template<class T>
class ConstIterator {

private:
    const BaseList<T>& list;
    Node<T>* current;

public:
    ConstIterator(const BaseList<T>&);
    ConstIterator(const ConstIterator<T>&);
    ~ConstIterator();

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

    const T& get() const;

    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);
    operator T();
    const T& operator &() const;

};

#endif
