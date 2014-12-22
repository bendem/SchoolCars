#include "formatters/CarFormatter.hpp"

String CarFormatter::format() const {
    stringstream ss;
    String title("= Car project '");
    title += this->obj.getName() + "' =";

    ss
        << "    " << String('=', title.length()) << endl
        << "    " << title << endl
        << "    " << String('=', title.length()) << endl << endl
        << "    Price:      " << this->obj.getPrice() << " EUR" << endl << endl
        << "    Model" << endl
        << "    | Name:     " << this->obj.getModel().getName() << endl
        << "    | BaseCost: " << this->obj.getModel().getBaseCost() << " EUR" << endl
        << "    | Diesel:   " << (this->obj.getModel().isDiesel() ? "yes" : "no") << endl
        << "    | Power:    " << this->obj.getModel().getPower() << endl
        ;
    List<Option> options(this->obj.getOptions());
    if(!options.isEmpty()) {
        ss << endl << "    Options" << endl;
    }
    ConstIterator<Option> it(options);
    while(!it.end()) {
        ss << "    | [" << (&it).getCode() << "] " << (&it).getName() << ": " << (&it).getPrice() << " EUR" << endl;
        ++it;
    }

    return ss.str();
}
