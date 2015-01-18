#include "formatters/ContractFormatter.hpp"

String ContractFormatter::format(unsigned int tabs) const {
    String tab(' ', tabs);
    stringstream ss;

    stringstream titleStream;
    titleStream
        << "= Contract " << green << '#' << this->obj.getId() << reset
        << " (" << yellow << this->obj.getDate().format("%d-%m-%y") << reset << ") =";

    String title = titleStream.str();

    ss
        << tab << String('=', title.length() - 18) << endl
        << tab << title << endl
        << tab << String('=', title.length() - 18) << endl << endl
        << tab << "Seller ID: " << this->obj.getSellerId() << endl
        << tab << "Client ID: " << this->obj.getClientId() << endl
        << tab << "Car:       " << endl
        << CarFormatter(this->obj.getCar()).format(tabs + 4) << endl
        << tab << "Price:     " << this->obj.getCar().getPrice() << " EUR" << endl
        << tab << "Discount:  -" << this->obj.getDiscount() << " EUR" << endl
        << tab << "-------------------------------" << endl
        << tab << "Total:     " << this->obj.getCar().getPrice() - this->obj.getDiscount() << " EUR" << endl
        ;

    return ss.str();
}
