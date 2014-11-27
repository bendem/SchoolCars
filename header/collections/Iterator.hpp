#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "collections/BaseList.hpp"

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

    bool end();
    void reset();
    T remove();
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    operator T();
    T& operator &();

    Iterator<T>& operator=(const Iterator<T>&);

};

#endif
