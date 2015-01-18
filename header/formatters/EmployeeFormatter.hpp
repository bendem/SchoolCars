#ifndef EMPLOYEEFORMATTER_HPP
#define EMPLOYEEFORMATTER_HPP

#include "Employee.hpp"
#include "utils/Formatter.hpp"
#include "utils/TermUtils.hpp"

class EmployeeFormatter : public Formatter<Employee> {

public:
    EmployeeFormatter(const Employee& p) : Formatter(p) {}
    String format(unsigned int) const;

};

#endif
