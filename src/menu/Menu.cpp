#include <utils/TermUtils.hpp>
#include "menu/Menu.hpp"

template<class T>
Menu<T>::Menu(const String& title, bool useArrows) {
    unsigned int width = title.length() + 20;

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
    this->useArrows = useArrows;
}

template<class T>
Menu<T>::Menu(const Menu<T>& param) {
    this->title = param.title;
    this->entries = List< MenuEntry<T> >(param.entries);
}

template<class T>
MenuEntry<T> Menu<T>::chooseWithArrows() {
    cout
        << saveCursorPosition
        << cursorUp(this->entries.size() + 1)
        << cursorRight(2);
    TermUtils::setRawInput(true);

    // First, let's get the first and last items in the menu
    // This is useful if the first or the last element is not selectable
    ConstIterator< MenuEntry<T> > it(this->entries);
    unsigned int first = 0, last = 0;
    bool foundFirst = false;
    unsigned int i = 0;
    while(!it.end()) {
        if(it.get().hasMethod()) {
            if(!foundFirst) {
                foundFirst = true;
                first = i;
            }
            last = i;
        }
        ++i;
        ++it;
    }
    Sanity::truthness(first != last && last != 0, "No selectable entry on this menu");

    // Now let's get the selection
    unsigned int selection = first;
    while(true) {
        int c = getchar();
        if(c == TermUtils::ENTER) {
            // Entry selected
            break;
        }

        // Sequence for arrows is ESCAPE, ARROW_ESCAPRE, ARROW_CODE
        // let's ignore eveything else
        if(c != TermUtils::ESCAPE) {
            continue;
        }
        if(getchar() != TermUtils::ARROW_ESCAPE) {
            continue;
        }
        switch(getchar()) {
            case TermUtils::ARROW_UP:
                // Prevents going before the first menu entry
                if(selection != first) {
                    cout << cursorUp;
                    // Skip menu separators
                    while(!this->entries.get(--selection).hasMethod()) {
                        cout << cursorUp;
                    }
                }
                break;
            case TermUtils::ARROW_DOWN:
                // Prevents going after the last menu entry
                if(selection != last) {
                    cout << cursorDown;
                    // Skip menu separators
                    while(!this->entries.get(++selection).hasMethod()) {
                        cout << cursorDown;
                    }
                }
                break;
        }
    }

    // Reset the poor terminal
    TermUtils::setRawInput(false);
    cout << restoreCursorPosition;

    return this->entries.get(selection);
}

template<class T>
MenuEntry<T> Menu<T>::chooseWithTyping() {
    String choice;
    cout << "    Your choice: ";
    cin >> choice;
    if(choice.length() == 0) {
        cout << " > Empty choice" << endl;
        return this->chooseWithTyping();
    }
    Optional< MenuEntry<T> > entry = this->entries.getFirstMatching(IdPredicate(choice));
    if(!entry.hasValue()) {
        cout << "> Invalid choice, try again :(" << endl << endl;
        return this->chooseWithTyping();
    }
    return entry.get();
}

template<class T>
Menu<T>& Menu<T>::addEntry(const MenuEntry<T>& entry) {
    this->entries.add(entry);
    return *this;
}

template<class T>
Menu<T>& Menu<T>::addEntry(const String& id, const String& text, void(T::*method)(void)) {
    this->entries.add(MenuEntry<T>(id, text, method));
    return *this;
}

template<class T>
void Menu<T>::display() const {
    cout << clear << this->title;

    ConstIterator< MenuEntry<T> > it(this->entries);
    while(!it.end()) {
        cout << it++.get() << endl;
    }
    cout << endl;
}

template<class T>
void Menu<T>::choose(T& object) {
    MenuEntry<T> entry = this->useArrows
            ? this->chooseWithArrows()
            : this->chooseWithTyping();
    cout
        << clear
        << endl
        << "    " << entry.getText() << endl
        << "   " << String('=', entry.getText().length()+2) << endl << endl;
    entry.callMethod(object);
}

#include "Application.hpp"
template class Menu<Application>;
