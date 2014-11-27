#ifndef STACK_HPP
#define STACK_HPP

#include "collections/BaseList.hpp"
#include "collections/List.hpp"

template<class T>
class Stack : public BaseList<T> {

public:
    void add(T const& param);
    T pop();

};

#endif
