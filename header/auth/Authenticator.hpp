#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include "Employee.hpp"
#include "predicates/LoginPredicate.hpp"
#include "utils/Logging.hpp"

class Authenticator {
private:
    Employee* currentUser;
    Authenticator(const Authenticator&) {}

public:
    Authenticator();
    // Authenticator doesn't own currentUser, it's inside Application::users

    bool quickLogin(const String&, const String&, List<Employee>&);
    bool login(List<Employee>&);
    void changePassword();
    void resetPassword(List<Employee>&);
    Employee& getCurrentUser();


};

#endif
