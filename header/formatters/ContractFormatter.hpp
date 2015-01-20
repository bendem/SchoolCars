#ifndef CONTRACTFORMATTER_HPP
#define CONTRACTFORMATTER_HPP

#include "Contract.hpp"
#include "formatters/CarFormatter.hpp"
#include "utils/Formatter.hpp"
#include "utils/TermUtils.hpp"

class ContractFormatter : public Formatter<Contract> {

public:
    ContractFormatter(const Contract& p) : Formatter<Contract>(p) {}
    String format(unsigned int) const;

};

#endif
