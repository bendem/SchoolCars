#ifndef MENU_HPP
#define MENU_HPP

#include "collections/List.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/String.hpp"

template<class T>
class Menu {

private:
    int width;
    String title;
    List< MenuEntry<T> >* entries;

public:
    Menu(const String&);
    Menu(const Menu<T>&);
    ~Menu();

    Menu<T>& addEntry(const MenuEntry<T>&);
    Menu<T>& addEntry(const String&, const String&, void(T::*)(void));
    void display() const;
    void choose(T&) const;

};

#endif
