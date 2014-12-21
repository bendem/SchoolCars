#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>

#include "utils/StreamUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Option {

private:
    String code;
    String name;
    float price;

public:
    Option(String = "", String = "", float = 0);
    Option(const Option&);

    void display() const;

    String getCode() const;
    void setCode(String code);

    String getName() const;
    void setName(String name);

    float getPrice() const;
    void setPrice(float price);

    void save(ostream&) const;
    void load(istream&);

    Option& operator++();
    Option operator++(int);
    Option& operator--();
    Option operator--(int);

    Option& operator=(const Option&);

    bool operator==(const Option&) const;

    friend ostream& operator<<(ostream&, const Option&);
    friend istream& operator>>(istream&, Option&);

};

#endif
