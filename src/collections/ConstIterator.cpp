#include "collections/ConstIterator.hpp"

template<class T>
ConstIterator<T>::ConstIterator(const BaseList<T>& param) : list(param), current(param.first) {}

template<class T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& param) : list(param.list), current(param.current) {}

template<class T>
ConstIterator<T>::~ConstIterator() {}

template<class T>
bool ConstIterator<T>::end() {
    return this->current == NULL;
}

template<class T>
void ConstIterator<T>::reset() {
    this->current = list.first;
}

template<class T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    Sanity::nullness(this->current, "Outside of the ConstIterator");

    this->current = this->current->next;
    return *this;
}

template<class T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    Sanity::nullness(this->current, "Outside of the ConstIterator");

    ConstIterator<T> tmp(*this);
    this->current = this->current->next;
    return tmp;
}

template<class T>
ConstIterator<T>::operator T() {
    return this->current->value;
}

//template<class T>
//ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator<T>& param) {
//    this->list = param.list;
//    this->current = param.current;
//    return *this;
//}

template class ConstIterator<int>;

#include "Option.hpp"
template class ConstIterator<Option>;

#include "Person.hpp"
template class ConstIterator<Person>;

#include "Employee.hpp"
template class ConstIterator<Employee>;
