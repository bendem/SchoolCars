#include "utils/TermUtils.hpp"

const String TermUtils::ESCAPE_SEQUENCE = "\033[";

void TermUtils::setEchoInput(bool echo) {
    // Get current settings
    termios settings;
    tcgetattr(STDIN_FILENO, &settings);

    // Change ICANON flag
    if (echo) {
        settings.c_lflag |= ECHO;
    } else {
        settings.c_lflag &= ~(ECHO);
    }

    // Apply new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void TermUtils::setRawInput(bool isRaw) {
    // Get current settings
    termios settings;
    tcgetattr(STDIN_FILENO, &settings);

    // Change ICANON flag
    if (isRaw) {
        settings.c_lflag &= ~(ICANON);
        settings.c_lflag &= ~(ECHO);
    } else {
        settings.c_lflag |= ICANON;
        settings.c_lflag |= ECHO;
    }

    // Apply new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

// Manipulators without args
ostream& saveCursorPosition(ostream& os)    { return os << TermUtils::ESCAPE_SEQUENCE << 's'; }
ostream& restoreCursorPosition(ostream& os) { return os << TermUtils::ESCAPE_SEQUENCE << 's'; }
ostream& clear(ostream& os) { return os << ClearManip(true); }
ostream& cursorUp(ostream& os)    { return os << CursorMoveManip(1, 'A'); }
ostream& cursorDown(ostream& os)  { return os << CursorMoveManip(1, 'B'); }
ostream& cursorLeft(ostream& os)  { return os << CursorMoveManip(1, 'D'); }
ostream& cursorRight(ostream& os) { return os << CursorMoveManip(1, 'C'); }
ostream& black(ostream& os)   { return os << TermUtils::ESCAPE_SEQUENCE << "30m"; }
ostream& red(ostream& os)     { return os << TermUtils::ESCAPE_SEQUENCE << "31m"; }
ostream& green(ostream& os)   { return os << TermUtils::ESCAPE_SEQUENCE << "32m"; }
ostream& yellow(ostream& os)  { return os << TermUtils::ESCAPE_SEQUENCE << "33m"; }
ostream& blue(ostream& os)    { return os << TermUtils::ESCAPE_SEQUENCE << "34m"; }
ostream& magenta(ostream& os) { return os << TermUtils::ESCAPE_SEQUENCE << "35m"; }
ostream& cyan(ostream& os)    { return os << TermUtils::ESCAPE_SEQUENCE << "36m"; }
ostream& white(ostream& os)   { return os << TermUtils::ESCAPE_SEQUENCE << "37m"; }
ostream& reset(ostream& os)   { return os << TermUtils::ESCAPE_SEQUENCE << "0m"; }

ostream& operator<<(ostream& os, const ClearManip& m) {
    os << TermUtils::ESCAPE_SEQUENCE << 2 << 'J';
    if(m.resetPosition) {
        os << cursorPosition(1, 1);
    }
    return os;
}
ClearManip clear(bool resetPos) { return ClearManip(resetPos); }

ostream& operator<<(ostream& os, const CursorMoveManip& m) {
    return os << TermUtils::ESCAPE_SEQUENCE << m.nb << m.c;
}
CursorMoveManip cursorUp(unsigned int nb = 1) { return CursorMoveManip(nb, 'A'); }
CursorMoveManip cursorDown(unsigned int nb = 1) { return CursorMoveManip(nb, 'B'); }
CursorMoveManip cursorLeft(unsigned int nb = 1) { return CursorMoveManip(nb, 'D'); }
CursorMoveManip cursorRight(unsigned int nb = 1) { return CursorMoveManip(nb, 'C'); }

ostream& operator<<(ostream& os, const CursorSetPosManip& m) {
    return os << TermUtils::ESCAPE_SEQUENCE << m.y << ';' << m.x << 'H';
}
CursorSetPosManip cursorPosition(unsigned int x, unsigned int y) { return CursorSetPosManip(x, y); }
