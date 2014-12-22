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
T List<T>::get(unsigned int index) const {
    Sanity::truthness(index < this->nbElems, "Index out of bounds");

    if(index == 0) {
        return this->first->value;
    }

    ConstIterator<T> it(*this);
    unsigned int i = 0;
    while(true) {
        if(i++ == index) {
            return it;
        }
        ++it;
    }
}

template<class T>
Optional<T> List<T>::getFirstMatching(const Predicate<T>& predicate) {
    Iterator<T> it(*this);
    while(!it.end()) {
        if(predicate.test(it)) {
            return Optional<T>(&it.get());
        }
        ++it;
    }
    return Optional<T>();
}

template class List<int>;

#include "Option.hpp"
template class List<Option>;

#include "Person.hpp"
template class List<Person>;

#include "Employee.hpp"
template class List<Employee>;

#include "Application.hpp"
#include "menu/MenuEntry.hpp"
template class List< MenuEntry<Application> >;

#include "Client.hpp"
template class List<Client>;

#include "utils/String.hpp"
template class List<String>;

#include "Model.hpp"
template class List<Model>;

#include "Contract.hpp"
template class List<Contract>;

#include "table/TableLine.hpp"
template class List<TableLine>;
