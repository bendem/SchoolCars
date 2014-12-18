#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <fstream>

#include "utils/StreamUtils.hpp"
#include "utils/String.hpp"

using namespace std;

class Model {
private:
    String name;
    int power;
    bool diesel;
    float baseCost;

public:
    Model(const String& name = "", int power = 0, bool diesel = false, float baseCost = 0)
        : name(name), power(power), diesel(diesel), baseCost(baseCost) {}
    Model(const Model&);
    virtual ~Model() {}

    void display() const;

    int getPower() const;
    void setPower(int power);

    const String& getName() const;
    void setName(const String& name);

    bool isDiesel() const;
    void setDiesel(bool diesel);

    float getBaseCost() const;
    void setBaseCost(float baseCost);

    Model& operator=(const Model&);

    bool operator==(const Model&);

    void save(ofstream&) const;
    void load(ifstream&);

    friend ostream& operator<<(ostream&, const Model&);
    friend istream& operator>>(istream&, Model&);
};

#endif
