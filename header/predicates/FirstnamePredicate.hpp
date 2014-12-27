#ifndef FIRSTNAMEPREDICATE_HPP
#define FIRSTNAMEPREDICATE_HPP

#include "Employee.hpp"
#include "utils/Predicate.hpp"
#include "utils/String.hpp"

class FirstnamePredicate : public Predicate<Employee> {

private:
    String name;

public:
    FirstnamePredicate(const String& name) : name(name) {}
    bool test(const Employee& param) const { return param.getFirstname() == this->name; }

};

#endif
