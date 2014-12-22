#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <iostream>

#include "Car.hpp"
#include "utils/Date.hpp"

using namespace std;

class Contract {

private:
    unsigned int id;
    unsigned int sellerId;
    unsigned int clientId;
    Date date;
    Car* car;
    float discount;

public:
    Contract();
    Contract(unsigned int, unsigned int, unsigned int, const Date&, const Car&, float = 0);
    Contract(const Contract&);
    ~Contract();

    unsigned int getId() const;
    unsigned int getSellerId() const;
    unsigned int getClientId() const;
    const Date& getDate() const;
    Date& getDate();
    const Car& getCar() const;
    Car& getCar();
    void setCar(const Car&);
    float getDiscount() const;
    void setDiscount(float);

    bool operator==(const Contract&) const;
    bool operator!=(const Contract&) const;
    bool operator>(const Contract&) const;
    bool operator<(const Contract&) const;
    bool operator>=(const Contract&) const;
    bool operator<=(const Contract&) const;

    Contract& operator=(Contract);

    void save(ostream&) const;
    void load(istream&);

    friend ostream& operator<<(ostream&, const Contract&);

};

#endif
