#include "collections/BaseList.hpp"

template<class T>
BaseList<T>::BaseList() {
    this->first = NULL;
    this->nbElems = 0;
}

template<class T>
BaseList<T>::BaseList(const BaseList<T>& list) {
    this->first = NULL;
    this->nbElems = 0;

    ConstIterator<T> it(list);
    while(!it.end()) {
        this->add((T) it++);
    }
}

template<class T>
BaseList<T>::~BaseList() {
    this->clear();
}

template<class T>
void BaseList<T>::add(const T& param) { throw logic_error("That method is abstract"); }

template<class T>
bool BaseList<T>::isEmpty() const {
    return this->nbElems == 0;
}

template<class T>
int BaseList<T>::size() const {
    return this->nbElems;
}

template<class T>
void BaseList<T>::remove(int index) {
    Sanity::truthness(index < nbElems && index >= 0, "Index must be lower than the list's size");

    Iterator<T> it(*this);

    int i = 0;
    while(i < index) {
        ++i;
        it++;
    }
    it.remove();
}

template<class T>
void BaseList<T>::clear() {
    Node<T>* node = this->first;
    Node<T>* prev;

    while(node) {
        prev = node;
        node = node->next;
        delete prev;
    }
    this->nbElems = 0;
}

template<class T>
void BaseList<T>::addAll(const BaseList& toAdd) {
    ConstIterator<T> it(toAdd);
    while(!it.end()) {
        this->add(&it);
    }
}

template<class T>
bool BaseList<T>::contains(const T& param) const {
    ConstIterator<T> it(*this);
    while(!it.end()) {
        if((T) it++ == param) {
            return true;
        }
    }
    return false;
}

template<class T>
BaseList<T>& BaseList<T>::operator=(const BaseList<T>& param) {
    this->clear();
    ConstIterator<T> it(param);
    while(!it.end()) {
        this->add((T) it++);
    }
    return *this;
}

template<class T>
void BaseList<T>::display() const {
    ConstIterator<T> it(*this);
    while(!it.end()) {
        cout << (T) it++ << endl;
    }
}

template class BaseList<int>;

#include "Option.hpp"
template class BaseList<Option>;

#include "Person.hpp"
template class BaseList<Person>;

#include "Employee.hpp"
template class BaseList<Employee>;

#include "Application.hpp"
#include "menu/MenuEntry.hpp"
template class BaseList< MenuEntry<Application> >;

#include "Client.hpp"
template class BaseList<Client>;

#include "utils/String.hpp"
template class BaseList<String>;

#include "Model.hpp"
template class BaseList<Model>;
