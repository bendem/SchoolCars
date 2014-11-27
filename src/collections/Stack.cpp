#include "collections/Stack.hpp"

template<class T>
void Stack<T>::add(T const& param) {
    Node<T>* tmp = new Node<T>;
    tmp->value = T(param);
    tmp->next = this->first;
    this->first = tmp;
    ++this->nbElems;
}

template<class T>
T Stack<T>::pop() {
    T elem(this->first->value);

    Node<T>* tmp = this->first;
    this->first = this->first->next;
    delete tmp;

    return elem;
}

template class Stack<int>;

#include "Option.hpp"
template class Stack<Option>;
