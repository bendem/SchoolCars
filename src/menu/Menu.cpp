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
    unsigned int selected = 0;
    TermUtils::pushCursorPosition();
    TermUtils::moveCursorUp(this->entries.size() + 1);
    TermUtils::moveCursorRight(2);
    TermUtils::setRawInput(true);
    while(true) {
        int c = getchar();
        if(c == TermUtils::ENTER) {
            break;
        }
        if(c != TermUtils::ESCAPE) {
            continue;
        }
        if(getchar() != TermUtils::ARROW_ESCAPE) {
            continue;
        }
        switch(getchar()) {
            // TODO Checks if first or last entry has no method
            case TermUtils::ARROW_UP:
                if(selected != 0) {
                    TermUtils::moveCursorUp();
                    while(!this->entries.get(--selected).hasMethod()) {
                        TermUtils::moveCursorUp();
                    }
                }
                break;
            case TermUtils::ARROW_DOWN:
                if(selected != this->entries.size()-1) {
                    TermUtils::moveCursorDown();
                    while(!this->entries.get(++selected).hasMethod()) {
                        TermUtils::moveCursorDown();
                    }
                }
                break;
            default:
                // ignore
                break;
        }
    }
    TermUtils::setRawInput(false);
    TermUtils::popCursorPosition();
    return this->entries.get(selected);
}

template<class T>
MenuEntry<T> Menu<T>::chooseWithTyping() {
    String choice;
    cout << "    Your choice: ";
    cin >> choice;
    Optional< MenuEntry<T> > entry = this->entries.getFirstMatching(IdPredicate(choice));
    if(!entry.hasValue()) {
        cout << "> Invalid choice, try again :(" << endl << endl;
        return this->chooseWithArrows();
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
    TermUtils::clearScreen();
    cout << this->title;

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
    TermUtils::clearScreen();
    cout
            << endl
            << "    " << entry.getText() << endl
            << "   " << String('=', entry.getText().length()+2) << endl << endl;
    entry.callMethod(object);
}

#include "Application.hpp"
template class Menu<Application>;
