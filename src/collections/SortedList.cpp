#include "collections/SortedList.hpp"

template<class T>
void SortedList<T>::add(const T& param) {
    Node<T>* newNode = new Node<T>(param, NULL);

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

template<class T>
bool SortedList<T>::contains(const T& param) const {
    ConstIterator<T> it(*this);
    while(!it.end()) {
        if((T) it == param) {
            return true;
        }
        // Addition for sorted lists
        if((T) it > param) {
            return false;
        }
        ++it;
    }
    return false;
}

template class SortedList<int>;

#include "Person.hpp"
template class SortedList<Person>;

#include "Employee.hpp"
template class SortedList<Employee>;
