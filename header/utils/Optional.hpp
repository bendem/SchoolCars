#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <cstddef>

/**
 * Represents an optional mutable value.
 */
template<class T>
class Optional {

private:
    T* value;

public:
    Optional() : value(NULL) {}
    Optional(T *value) : value(value) {}
    Optional(const Optional<T>& param) : value(param.value) {}
    ~Optional() { /* this->value doesn't belong to this object, it will be deleted elsewhere ;) */ }

    bool hasValue() const { return this->value != NULL; }

    /**
     * The optional value contained by this object.
     * This method should not be called if hasValue returns false!
     */
    T& get() { return *this->value; }

    Optional<T>& operator=(const Optional<T> param) { this->value = param.value; return *this; }

};

#endif
