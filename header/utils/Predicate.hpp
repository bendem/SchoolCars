#ifndef PREDICATE_HPP
#define PREDICATE_HPP

template<class T>
class Predicate {

public:
    virtual bool test(const T&) const = 0;

};

#endif
