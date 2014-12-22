#include "menu/Menu.hpp"

template<class T>
Menu<T>::Menu(const String& title) {
    int width = title.length() + 20;

    // Constructing title
    stringstream ss;
    ss << "    " << String('=', width) << endl
        << "    ="
        << String(' ', (width - title.length()) / 2 - 1)
        << title
        << String(' ', (width - title.length()) / 2 - (title.length() % 2 ? 0 : 1))
        << "="
        << endl
        << "    " << String('=', width) << endl << endl;

    this->title = ss.str();

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
Menu<T>& Menu<T>::addEntry(const String& id, const String& text, void(T::*method)(void)) {
    this->entries->add(MenuEntry<T>(id, text, method));
    return *this;
}

template<class T>
void Menu<T>::display() const {
    cout << this->title;

    ConstIterator< MenuEntry<T> > it(*this->entries);
    while(!it.end()) {
        cout << it++.get() << endl;
    }
    cout << endl;
}

template<class T>
void Menu<T>::choose(T& object) const {
    String choice;

    cout << "    Your choice: ";
    cin >> choice;

    Iterator< MenuEntry<T> > it(*this->entries);
    while(!it.end()) {
        if(it.get() == choice && it.get().hasMethod()) {
            cout << endl;
            it.get().callMethod(object);
            return;
        }
        ++it;
    }
    cout << "> Invalid choice, try again :(" << endl << endl;
    this->choose(object);
}

#include "Application.hpp"
template class Menu<Application>;
