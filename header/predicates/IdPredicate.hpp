#ifndef IDPREDICATE_HPP
#define IDPREDICATE_HPP

#include "utils/Predicate.hpp"

template<class T>
class IdPredicate : public Predicate<T> {
private:
    int id;

public:
    IdPredicate(int id) : id(id) {}
    bool test(const T& param) const { return param.getId() == this->id; }

};

#endif
