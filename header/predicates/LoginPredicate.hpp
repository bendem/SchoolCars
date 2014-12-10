#ifndef LOGINPREDICATE_HPP
#define LOGINPREDICATE_HPP

#include "Employee.hpp"
#include "utils/Predicate.hpp"

class LoginPredicate : public Predicate<Employee> {

private:
    String login;

public:
    LoginPredicate(const String& login) : login(login) {}
    bool test(const Employee& param) const { return param.getLogin() == this->login; }

};

#endif
