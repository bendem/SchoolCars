#include "collections/List.hpp"

template<class T>
void List<T>::add(const T& para) {
    // Preparing new node
    Node<T>* tmp = new Node<T>(para, NULL);

    if(!this->first) {
        // Adding first
        this->first = tmp;

    } else {
        // Adding at the end
        Node<T>* current = this->first;
        while(current->next) {
            current = current->next;
        }
        current->next = tmp;
    }
    ++this->nbElems;
}

template<class T>
T List<T>::get(int index) const {
    Sanity::truthness(index < this->nbElems, "Index out of bounds" + index);

    ConstIterator<T> it(*this);
    int i = 0;
    while (i < index) {
        ++i;
        if(i == index) {
            return it;
        }
        it++;
    }
}

template class List<int>;

#include "Option.hpp"
template class List<Option>;

#include "Person.hpp"
template class List<Person>;

#include "Employee.hpp"
template class List<Employee>;
