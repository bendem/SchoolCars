#include "formatters/CarFormatter.hpp"

String CarFormatter::format(int tabs) const {
    String tab(' ', tabs);
    stringstream ss;
    String title("= Car project '");
    title += this->obj.getName() + "' =";

    ss
        << tab << String('=', title.length()) << endl
        << tab << title << endl
        << tab << String('=', title.length()) << endl << endl
        << tab << "Price:      " << this->obj.getPrice() << " EUR" << endl << endl
        << tab << "Model" << endl
        << tab << "| Name:     " << this->obj.getModel().getName() << endl
        << tab << "| BaseCost: " << this->obj.getModel().getBaseCost() << " EUR" << endl
        << tab << "| Diesel:   " << (this->obj.getModel().isDiesel() ? "yes" : "no") << endl
        << tab << "| Power:    " << this->obj.getModel().getPower() << endl
        ;
    List<Option> options(this->obj.getOptions());
    if(!options.isEmpty()) {
        ss << endl << tab << "Options" << endl;
    }
    ConstIterator<Option> it(options);
    while(!it.end()) {
        ss << tab << "| [" << it.get().getCode() << "] " << it.get().getName() << ": " << it.get().getPrice() << " EUR" << endl;
        ++it;
    }

    return ss.str();
}
