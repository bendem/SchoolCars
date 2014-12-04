#include "collections/Iterator.hpp"

template<class T>
Iterator<T>::Iterator(BaseList<T>& param)
    : list(param), current(param.first), prec(NULL) {}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& param)
    : list(param.list), current(param.current), prec(param.prec) {}

template<class T>
Iterator<T>::~Iterator() {}

template<class T>
bool Iterator<T>::end() {
    return this->current == NULL;
}

template<class T>
void Iterator<T>::reset() {
    this->current = list.first;
    this->prec = NULL;
}

template<class T>
T Iterator<T>::remove() {
    T elem(this->current->value);

    if(!this->prec) {
        // Removing first element
        this->list.first = this->current->next;
        delete this->current;
        this->current = this->list.first;
        return elem;
    }

    this->prec->next = this->current->next;
    delete this->current;
    this->current = this->prec->next;
    return elem;
}

template<class T>
Iterator<T>& Iterator<T>::operator++() {
    Sanity::nullness(this->current, "Outside of the iterator");

    this->prec = this->current;
    this->current = this->current->next;
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int) {
    Sanity::nullness(this->current, "Outside of the iterator");

    Iterator<T> tmp(*this);
    this->prec = this->current;
    this->current = this->current->next;
    return tmp;
}

template<class T>
Iterator<T>::operator T() {
    return this->current->value;
}

template<class T>
T& Iterator<T>::operator&() {
    return this->current->value;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(Iterator<T> const& param) {
    this->list = param.list;
    this->current = param.current;
    this->prec = param.prec;
    return *this;
}

template class Iterator<int>;

#include "Option.hpp"
template class Iterator<Option>;

#include "Person.hpp"
template class Iterator<Person>;

#include "Employee.hpp"
template class Iterator<Employee>;

#include "Application.hpp"
#include "menu/MenuEntry.hpp"
template class Iterator< MenuEntry<Application> >;

#include "Client.hpp"
template class Iterator<Client>;

#include "utils/String.hpp"
template class Iterator<String>;

#include "Model.hpp"
template class Iterator<Model>;
