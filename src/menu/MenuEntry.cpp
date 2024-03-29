#include "menu/MenuEntry.hpp"

template<class T>
MenuEntry<T>::MenuEntry(const String& id, const String& text, void(T::*method)(void)) {
    this->id = id;
    this->text = text;
    this->method = method;
}

template<class T>
MenuEntry<T>::MenuEntry(const MenuEntry& param) {
    this->id = param.id;
    this->text = param.text;
    this->method = param.method;
}

template<class T>
String MenuEntry<T>::toString() const {
    ostringstream os;
    os << "  ";
    if(this->method) {
        os << "  " << yellow << this->id << reset << '.';
    } else {
        os << String(this->id, 5);
    }
    os << '\t' << this->text;
    return os.str();
}

template<class T>
void MenuEntry<T>::callMethod(T& param) const {
    (param.*this->method)();
}

template<class T>
bool MenuEntry<T>::operator==(const MenuEntry& param) const {
    return this->id == param.id
        && this->text == param.text
        && this->method == param.method;
}


template<class T>
bool MenuEntry<T>::operator==(const String& param) const {
    return this->id == param;
}

template<class T>
MenuEntry<T>& MenuEntry<T>::operator=(const MenuEntry& param) {
    this->id = param.id;
    this->text = param.text;
    this->method = param.method;
    return *this;
}

#include "Application.hpp"
template class MenuEntry<Application>;
