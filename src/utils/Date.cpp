#include "utils/Date.hpp"

const unsigned int Date::MONTHES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    this->day = now->tm_mday;
    this->month = now->tm_mon + 1;
    this->year = now->tm_year + 1900;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
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

bool Date::validate(unsigned int day, unsigned int month, unsigned int year) {
    if(month < 1 || month > 12) {
        return false;
    }
    unsigned int daysInMonth = Date::MONTHES[month - 1];
    if(month == 1 && Date::isLeap(year)) {
        ++daysInMonth;
    }
    return day <= daysInMonth;
}

bool Date::isLeap(unsigned int year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

unsigned int Date::getDay() const {
    return this->day;
}

unsigned int Date::getMonth() const {
    return this->month;
}

unsigned int Date::getYear() const {
    return this->year;
}

void Date::setDay(unsigned int day) {
    Sanity::truthness(Date::validate(day, this->month, this->year), "Invalid date");

    this->day = day;
}

void Date::setMonth(unsigned int month) {
    Sanity::truthness(Date::validate(this->day, month, this->year), "Invalid date");

    this->month = month;
}

void Date::setYear(unsigned int year) {
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
    this->day = StreamUtils::read<unsigned int>(is);
    this->month = StreamUtils::read<unsigned int>(is);
    this->year = StreamUtils::read<unsigned int>(is);
}

ostream& operator<<(ostream& os, const Date& param) {
    return os
        << "Date{"
        << "day=" << param.day
        << ", month=" << param.month
        << ", year=" << param.year
        << "}";
}
