#ifndef TERMUTILS_HPP
#define TERMUTILS_HPP

#include <iostream>

#include <termios.h>
#include <unistd.h>

#include "utils/String.hpp"

class TermUtils {

private:
    static const String ESCAPE_SEQUENCE;

public:
    static void clearScreen(bool = true);

    static void pushCursorPosition();
    static void popCursorPosition();
    static void setCursorPosition(unsigned int, unsigned int);
    static void moveCursorUp(unsigned int = 1);
    static void moveCursorDown(unsigned int = 1);
    static void moveCursorLeft(unsigned int = 1);
    static void moveCursorRight(unsigned int = 1);

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

#endif
