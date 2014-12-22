#include <formatters/CarFormatter.hpp>
#include "formatters/ContractFormatter.hpp"

String ContractFormatter::format(int tabs) const {
    String tab(' ', tabs);
    stringstream ss;

    stringstream titleStream;
    titleStream
        << "= Contract #" << this->obj.getId()
        << " (" << this->obj.getDate().format("%d-%m-%y") << ") =";

    String title = titleStream.str();

    ss
        << tab << String('=', title.length()) << endl
        << tab << title << endl
        << tab << String('=', title.length()) << endl << endl
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
