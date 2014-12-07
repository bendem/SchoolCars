#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include "Car.hpp"
#include "utils/Date.hpp"

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

    int getId() const;
    int getSellerId() const;
    int getClientId() const;
    const Date& getDate() const;
    Date& getDate();
    Car* getCar() const;
    float getDiscount() const;

};

#endif
