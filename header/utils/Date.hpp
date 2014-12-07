#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

#include "utils/Sanity.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

class Date {

private:
    static const int MONTHES[12];

    static bool validate(int, int, int);
    static bool isLeap(int);

    int day;
    int month;
    int year;

public:
    Date(int, int, int);
    Date(const Date&);
    ~Date() {}

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDay(int);
    void setMonth(int);
    void setYear(int);

    Date& operator=(const Date&);

    void save(ostream&) const;
    void load(istream&);

};

#endif