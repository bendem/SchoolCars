#include "utils/Logging.hpp"

String time(const String& name) {
    time_t rawtime;
    char buff[11];
    time(&rawtime);
    strftime(buff, sizeof(buff), "[%H:%M:%S]", localtime(&rawtime));
    return String(buff) + " [" + name + "] ";
}
