#include "formatters/CarFormatter.hpp"

String CarFormatter::format(unsigned int tabs) const {
    String tab(' ', tabs);
    ostringstream ss;
    ostringstream titlestream;
    titlestream << "= Car project '" << green << this->obj.getName() << reset << "' =";
    String title = titlestream.str();

    ss
        << tab << String('=', title.length() - 9) << endl // -4 for reset, -5 for the color
        << tab << title << endl
        << tab << String('=', title.length() - 9) << endl << endl
        << tab << "Price:      " << this->obj.getPrice() << " EUR" << endl << endl
        << tab << "Model" << endl
        << tab << "| Name:     " << this->obj.getModel().getName() << endl
        << tab << "| BaseCost: " << this->obj.getModel().getBaseCost() << " EUR" << endl
        << tab << "| Diesel:   " << String::valueOf(this->obj.getModel().isDiesel()) << endl
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
