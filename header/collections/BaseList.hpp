#ifndef BASELIST_HPP
#define BASELIST_HPP

#include <iostream>
#include "utils/Sanity.hpp"

using namespace std;

template<class T>
struct Node {
    T value;
    Node* next;
};

template<class T> class BaseList;

template<class T> class ConstIterator;
template<class T> class Iterator;
#include "collections/ConstIterator.hpp"
#include "collections/Iterator.hpp"

template<class T>
class BaseList {

protected:
    Node<T>* first;
    int nbElems;

public:
    BaseList();
    BaseList(const BaseList<T>&);
    ~BaseList();

    virtual void add(const T&) = 0;

    bool isEmpty() const;
    int size() const;
    void remove(int);
    void clear();

    // Eww :(
    void display() const;

    friend class ConstIterator<T>;
    friend class Iterator<T>;

};

#endif
