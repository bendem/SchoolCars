#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <sstream>

#include "utils/String.hpp"

/**
 * Represents an entry for a Menu.
 */
template<class T>
class MenuEntry {

private:
    String id;
    String text;
    void(T::*method)(void);

public:

    /**
     * Constructs an entry having an identifier, a text and a method to call.
     *
     * If the method pointer provided is null, the entry is not choosable and
     * its identifier will be duplicated for times (as a separator).
     */
    MenuEntry(const String&, const String&, void(T::*)(void));
    MenuEntry(const MenuEntry&);

    String toString() const;
    void callMethod(T&) const;
    bool hasMethod() const { return this->method != NULL; }
    const String& getText() const { return this->text; }

    bool operator==(const MenuEntry&) const;
    bool operator==(const String&) const;

    MenuEntry<T>& operator=(const MenuEntry&);

};

template<class T>
ostream& operator<<(ostream& os, const MenuEntry<T>& entry) {
    return os << entry.toString();
}

#endif
