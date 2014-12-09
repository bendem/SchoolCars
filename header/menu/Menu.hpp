#ifndef MENU_HPP
#define MENU_HPP

#include <sstream>

#include "collections/List.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/String.hpp"

using namespace std;

template<class T>
class Menu {

private:
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
