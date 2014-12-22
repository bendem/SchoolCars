#include "utils/Date.hpp"

const int Date::MONTHES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    this->day = now->tm_mday;
    this->month = now->tm_mon + 1;
    this->year = now->tm_year + 1900;
}

Date::Date(int day, int month, int year) {
    Sanity::truthness(Date::validate(day, month, year), "Invalid date");

    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const Date& param) {
    this->day = param.day;
    this->month = param.month;
    this->year = param.year;
}

bool Date::validate(int day, int month, int year) {
    if(month < 1 || month > 12 || year < 0) {
        return false;
    }
    int daysInMonth = Date::MONTHES[month - 1];
    if(month == 1 && Date::isLeap(year)) {
        ++daysInMonth;
    }
    return day <= daysInMonth;
}

bool Date::isLeap(int year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int Date::getDay() const {
    return this->day;
}

int Date::getMonth() const {
    return this->month;
}

int Date::getYear() const {
    return this->year;
}

void Date::setDay(int day) {
    Sanity::truthness(Date::validate(day, this->month, this->year), "Invalid date");

    this->day = day;
}

void Date::setMonth(int month) {
    Sanity::truthness(Date::validate(this->day, month, this->year), "Invalid date");

    this->month = month;
}

void Date::setYear(int year) {
    Sanity::truthness(Date::validate(this->day, this->month, year), "Invalid date");

    this->year = year;
}

String Date::format(String format) const {
    return format
        .replace("%d", String::valueOf(this->day))
        .replace("%m", String::valueOf(this->month))
        .replace("%y", String::valueOf(this->year));
}

Date& Date::operator=(const Date& param) {
    this->day = param.day;
    this->month = param.month;
    this->year = param.year;
    return *this;
}

bool Date::operator==(const Date& param) const {
    return this->day == param.day
        && this->month == param.month
        && this->year == param.year;
}

bool Date::operator!=(const Date& param) const {
    return this->day != param.day
        || this->month != param.month
        || this->year != param.year;
}

bool Date::operator>(const Date& param) const {
    if(this->year > param.year) {
        return true;
    }
    if(this->year == param.year) {
        if(this->month > param.month) {
            return true;
        }
        if(this->month == param.month) {
            return this->day > param.day;
        }
    }
    return false;
}

bool Date::operator<(const Date& param) const {
    if(this->year < param.year) {
        return true;
    }
    if(this->year == param.year) {
        if(this->month < param.month) {
            return true;
        }
        if(this->month == param.month) {
            return this->day < param.day;
        }
    }
    return false;
}

bool Date::operator>=(const Date& param) const {
    return *this > param || *this == param;
}

bool Date::operator<=(const Date& param) const {
    return *this < param || *this == param;
}

void Date::save(ostream& os) const {
    StreamUtils::write(os, this->day);
    StreamUtils::write(os, this->month);
    StreamUtils::write(os, this->year);
}
void Date::load(istream& is) {
    this->day = StreamUtils::readInt(is);
    this->month = StreamUtils::readInt(is);
    this->year = StreamUtils::readInt(is);
}

ostream& operator<<(ostream& os, const Date& param) {
    return os
        << "Date{"
        << "day=" << param.day
        << ", month=" << param.month
        << ", year=" << param.year
        << "}";
}
