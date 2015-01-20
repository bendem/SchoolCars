#ifndef PREDICATE_HPP
#define PREDICATE_HPP

/**
 * Represents a boolean expression to apply on the specified type.
 */
template<class T>
class Predicate {

public:
    virtual ~Predicate() {}
    virtual bool test(const T&) const = 0;

};

#endif
