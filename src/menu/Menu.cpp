#include "menu/Menu.hpp"

template<class T>
Menu<T>::Menu(const String& title) {
    this->width = title.length() + 20;
    this->title = title;
    this->entries = new List< MenuEntry<T> >();
}

template<class T>
Menu<T>::Menu(const Menu<T>& param) {
    this->width = param.width;
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
    // TODO + Fix that shitty mess,
    // TODO + Cache that shit in the constructor since you can't change the title anyway
    cout << "    " << String('=', this->width) << endl;
    cout
        << "    ="
        << String(' ', (this->width - this->title.length()) / 2 - 1)
        << this->title
        << String(' ', (this->width - this->title.length()) / 2 - (this->title.length() % 2 ? 0 : 1))
        << "="
        << endl;
    cout << "    " << String('=', this->width) << endl << endl;

    ConstIterator< MenuEntry<T> > it(*this->entries);
    while(!it.end()) {
        cout << &it << endl;
        ++it;
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
        if(&it == choice && (&it).hasMethod()) {
            cout << endl;
            (&it).callMethod(object);
            return;
        }
        ++it;
    }
    cout << "> Invalid choice, try again :(" << endl << endl;
    this->choose(object);
}

#include "Application.hpp"
template class Menu<Application>;
