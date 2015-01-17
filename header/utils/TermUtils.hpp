#ifndef TERMUTILS_HPP
#define TERMUTILS_HPP

#include <iostream>

#include <termios.h>
#include <unistd.h>

#include "utils/String.hpp"

class TermUtils {

public:
    static const String ESCAPE_SEQUENCE;

    static void setEchoInput(bool echo);
    static void setRawInput(bool isRaw);

    enum Key {
        ESCAPE = 27,
        ARROW_ESCAPE = 91,
        ARROW_UP = 65,
        ARROW_DOWN = 66,
        ARROW_RIGHT = 67,
        ARROW_LEFT = 68,
        ENTER = 10,
    };

};

// Manipulators without args
ostream& saveCursorPosition(ostream&);
ostream& restoreCursorPosition(ostream&);
ostream& clear(ostream&);
ostream& cursorUp(ostream&);
ostream& cursorDown(ostream&);
ostream& cursorLeft(ostream&);
ostream& cursorRight(ostream&);
// Colors
ostream& black(ostream&);
ostream& red(ostream&);
ostream& green(ostream&);
ostream& yellow(ostream&);
ostream& blue(ostream&);
ostream& magenta(ostream&);
ostream& cyan(ostream&);
ostream& white(ostream&);
ostream& reset(ostream&);

// Manipulators with args
class ClearManip {
private:
    bool resetPosition;
public:
    explicit ClearManip(bool resetPos) : resetPosition(resetPos) {}
    friend ostream& operator<<(ostream&, const ClearManip&);
};
ClearManip clear(bool);

class CursorMoveManip {
private:
    unsigned int nb;
    char c;
public:
    explicit CursorMoveManip(unsigned int nb, char c) : nb(nb), c(c) {}
    friend ostream& operator<<(ostream&, const CursorMoveManip&);
};
CursorMoveManip cursorUp(unsigned int nb);
CursorMoveManip cursorDown(unsigned int nb);
CursorMoveManip cursorLeft(unsigned int nb);
CursorMoveManip cursorRight(unsigned int nb);

class CursorSetPosManip {
private:
    unsigned int x;
    unsigned int y;
public:
    explicit CursorSetPosManip(unsigned int x, unsigned int y) : x(x), y(y) {}
    friend ostream& operator<<(ostream&, const CursorSetPosManip&);
};
CursorSetPosManip cursorPosition(unsigned int x, unsigned int y);

#endif
