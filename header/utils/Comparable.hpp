#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP

template<class T>
class Comparable {

public:
    virtual ~Comparable() {}
    virtual int compareTo(const T&) const = 0;
    
    bool operator==(const T& param) const { return this->compareTo(param) == 0; }
    bool operator!=(const T& param) const { return this->compareTo(param) != 0; }
    bool operator> (const T& param) const { return this->compareTo(param) >  0; }
    bool operator< (const T& param) const { return this->compareTo(param) <  0; }
    bool operator>=(const T& param) const { return this->compareTo(param) >= 0; }
    bool operator<=(const T& param) const { return this->compareTo(param) <= 0; }

};

#endif
