#ifndef CLIENTIDPREDICATE_HPP
#define CLIENTIDPREDICATE_HPP

#include "Contract.hpp"
#include "utils/Predicate.hpp"

class ClientIdPredicate : public Predicate<Contract> {

private:
    unsigned int id;

public:
    ClientIdPredicate(unsigned int id) : id(id) {}
    bool test(const Contract& param) const { return param.getClientId() == this->id; }

};

#endif
