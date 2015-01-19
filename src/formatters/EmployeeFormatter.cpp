#include "formatters/EmployeeFormatter.hpp"

String EmployeeFormatter::format(unsigned int tabs) const {
    String tab(' ', tabs);
    stringstream ss;

    ss
        << tab << String('=', this->obj.getLogin().length() + 4) << endl
        << tab << "= " << green << this->obj.getLogin() << reset << " =" << endl
        << tab << String('=', this->obj.getLogin().length() + 4) << endl << endl
        << tab << "Id:        " << this->obj.getId() << endl
        << tab << "Login:     " << this->obj.getLogin() << endl
        << tab << "Password:  " << (this->obj.getPassword().isEmpty() ? "<empty>" : String('*', this->obj.getPassword().length())) << endl
        << tab << "Function:  " << this->obj.getFunction() << endl
        << tab << "Firstname: " << this->obj.getFirstname() << endl
        << tab << "Surname:   " << this->obj.getSurname() << endl;

    return ss.str();
}
