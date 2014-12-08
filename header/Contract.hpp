#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <iostream>

#include "Car.hpp"
#include "utils/Date.hpp"

using namespace std;

class Contract {

private:
    int id;
    int sellerId;
    int clientId;
    Date date;
    Car* car;
    float discount;

public:
    Contract(int, int, int, const Date&, Car*, float = 0);
    ~Contract();

    int getId() const;
    int getSellerId() const;
    int getClientId() const;
    const Date& getDate() const;
    Date& getDate();
    Car* getCar() const;
    float getDiscount() const;

    bool operator==(const Contract&) const;
    bool operator!=(const Contract&) const;
    bool operator>(const Contract&) const;
    bool operator<(const Contract&) const;
    bool operator>=(const Contract&) const;
    bool operator<=(const Contract&) const;

    void save(ostream&) const;
    void load(istream&);

    friend ostream& operator<<(ostream&, const Contract&);

};

#endif
