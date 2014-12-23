#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <iostream>

#include "utils/Comparable.hpp"
#include "utils/Sanity.hpp"
#include "utils/StreamUtils.hpp"

using namespace std;

/**
 * Represents a date by its day, month and year.
 */
class Date : public Comparable<Date> {

private:
    static const unsigned int MONTHS[12];

    static bool validate(unsigned int, unsigned int, unsigned int);
    static bool isLeap(unsigned int);

    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date();
    Date(unsigned int, unsigned int, unsigned int);
    Date(const Date&);
    ~Date() {}

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    void setDay(unsigned int);
    void setMonth(unsigned int);
    void setYear(unsigned int);

    String format(String) const;

    Date& operator=(const Date&);

    int compareTo(const Date&) const;

    void save(ostream&) const;
    void load(istream&);

    friend ostream& operator<<(ostream&, const Date&);

};

#endif
