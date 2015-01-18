#ifndef NAMEPREDICATE_HPP
#define NAMEPREDICATE_HPP

#include "Contract.hpp"
#include "utils/Predicate.hpp"

class NamePredicate : public Predicate<Contract> {

private:
    const String name;

public:
    NamePredicate(String name) : name(name) {}
    bool test(const Contract& param) const { return param.getCar().getName() == name; }

};

#endif
