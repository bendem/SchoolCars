#include "collections/SortedList.hpp"

template<class T>
void SortedList<T>::add(const T& param) {
    Node<T>* newNode = new Node<T>();
    newNode->value = T(param);

    if(!this->first || this->first->value >= param) {
        newNode->next = this->first;
        this->first = newNode;
        ++this->nbElems;
        return;
    }

    Node<T>* current = this->first->next;
    Node<T>* prec = this->first;
    while(current && current->value < param) {
        prec = current;
        current = current->next;
    }
    newNode->next = current;
    prec->next = newNode;

    ++this->nbElems;
}

template class SortedList<int>;

#include "Person.hpp"
template class SortedList<Person>;
