#include "utils/TermUtils.hpp"

const String TermUtils::ESCAPE_SEQUENCE = "\033[";

void TermUtils::clearScreen(bool resetPosition) {
    std::cout << ESCAPE_SEQUENCE << 2 << 'J';
    if(resetPosition) {
        setCursorPosition(1, 1);
    }
}
void TermUtils::pushCursorPosition() {
    std::cout << ESCAPE_SEQUENCE << 's';
}
void TermUtils::popCursorPosition() {
    std::cout << ESCAPE_SEQUENCE << 'u';
}
void TermUtils::setCursorPosition(unsigned int x, unsigned int y) {
    std::cout << ESCAPE_SEQUENCE << y << ';' << x << 'H';
}
void TermUtils::moveCursorUp(unsigned int nb) {
    std::cout << ESCAPE_SEQUENCE << nb << 'A';
}
void TermUtils::moveCursorDown(unsigned int nb) {
    std::cout << ESCAPE_SEQUENCE << nb << 'B';
}
void TermUtils::moveCursorLeft(unsigned int nb) {
    std::cout << ESCAPE_SEQUENCE << nb << 'D';
}
void TermUtils::moveCursorRight(unsigned int nb) {
    std::cout << ESCAPE_SEQUENCE << nb << 'C';
}

void TermUtils::setRawInput(bool isRaw) {
    termios settings;

    // Get current settings
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
