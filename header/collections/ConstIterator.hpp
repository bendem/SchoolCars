#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "BaseList.hpp"

template<class T>
class ConstIterator {

private:
    const BaseList<T>& list;
    Node<T>* current;

public:
    ConstIterator(const BaseList<T>&);
    ConstIterator(const ConstIterator<T>&);
    ~ConstIterator();

    bool end();
    void reset();
    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);
    operator T();
    const T& operator &() const;

};

#endif
