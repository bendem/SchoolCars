#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>
#include <fstream>

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

    void save(ofstream&) const;
    void load(ifstream&);

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
