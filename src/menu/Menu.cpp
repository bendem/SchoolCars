#include "menu/Menu.hpp"

template<class T>
const int Menu<T>::WIDTH = 30;

template<class T>
Menu<T>::Menu(const String& title) {
    this->title = title;
    this->entries = new List< MenuEntry<T> >();
}

template<class T>
Menu<T>::Menu(const Menu<T>& param) {
    this->title = param.title;
    this->entries = new List< MenuEntry<T> >(*param.entries);
}

template<class T>
Menu<T>::~Menu() {
    delete this->entries;
}

template<class T>
Menu<T>& Menu<T>::addEntry(const MenuEntry<T>& entry) {
    this->entries->add(entry);
    return *this;
}

template<class T>
Menu<T>& Menu<T>::addEntry(const String& id, const String& text, bool(T::*method)(void)) {
    this->entries->add(MenuEntry<T>(id, text, method));
    return *this;
}

template<class T>
void Menu<T>::display() const {
    // TODO + Fix that shitty mess,
    // TODO + Set size per menu (not static) based on title size,
    // TODO + Cache that shit in the constructor since you can't change the title anyway
    cout << "    " << String('=', Menu<T>::WIDTH) << endl;
    cout
        << "    ="
        << String(' ', (Menu<T>::WIDTH - this->title.length()) / 2 - 1)
        << this->title
        << String(' ', (Menu<T>::WIDTH - this->title.length()) / 2 - (this->title.length() % 2 ? 0 : 1))
        << "="
        << endl;
    cout << "    " << String('=', Menu<T>::WIDTH) << endl << endl;

    ConstIterator< MenuEntry<T> > it(*this->entries);
    while(!it.end()) {
        cout << (MenuEntry<T>) it << endl;
        ++it;
    }
    cout << endl;
}

#include "Application.hpp"
template class Menu<Application>;
