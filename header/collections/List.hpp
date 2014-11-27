#ifndef LIST_HPP
#define LIST_HPP

#include "collections/BaseList.hpp"
#include "collections/Iterator.hpp"
#include "utils/Sanity.hpp"

template<class E> class ListIterator;
template<class E> class ConstListIterator;

template<class T>
class List : public BaseList<T> {

public:
    void add(const T&);
    T get(int) const;

};

#endif
