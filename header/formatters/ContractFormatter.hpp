#ifndef CONTRACTFORMATTER_HPP
#define CONTRACTFORMATTER_HPP

#include "Contract.hpp"
#include "utils/Formatter.hpp"

class ContractFormatter : public Formatter<Contract> {

public:
    ContractFormatter(const Contract& p) : Formatter(p) {}
    String format(int) const;

};

#endif
