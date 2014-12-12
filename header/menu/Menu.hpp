#ifndef MENU_HPP
#define MENU_HPP

#include <sstream>

#include "collections/List.hpp"
#include "menu/MenuEntry.hpp"
#include "utils/String.hpp"

using namespace std;

/**
 * Represents a console menu interface.
 */
template<class T>
class Menu {

private:
    String title;
    List< MenuEntry<T> >* entries;

public:
    Menu(const String&);
    Menu(const Menu<T>&);
    ~Menu();

    /**
     * Adds a MenuEntry to the current Menu.
     * Entries are ordered based on the order they're added to the menu.
     */
    Menu<T>& addEntry(const MenuEntry<T>&);

    /**
     * Convenience method to add a MenuEntry.
     */
    Menu<T>& addEntry(const String&, const String&, void(T::*)(void));

    /**
     * Displays the menu.
     */
    void display() const;

    /**
     * Prompts the user to make a choice based on the menu entries and call
     * the corresponding method on the provided object.
     */
    void choose(T&) const;

};

#endif
