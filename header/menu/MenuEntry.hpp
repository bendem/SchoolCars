#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <sstream>

#include "utils/String.hpp"

template<class T>
class MenuEntry {

private:
    String id;
    String text;
    void(T::*method)(void);

public:
    MenuEntry(const String&, const String&, void(T::*)(void));
    MenuEntry(const MenuEntry&);

    String toString() const;
    void callMethod(T&) const;
    bool hasMethod() const { return this->method != NULL; }

    bool operator==(const MenuEntry&) const;
    bool operator==(const String&) const;

    MenuEntry<T>& operator=(const MenuEntry&);

};

template<class T>
ostream& operator<<(ostream& os, const MenuEntry<T>& entry) {
    return os << entry.toString();
}

#endif
