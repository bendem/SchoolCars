#ifndef METHODPOINTERUTLS_HPP
#define METHODPOINTERUTLS_HPP

class MethodPointerUtils {

public:

    template<class R, class T>
    static R callObjectMethod(T* object, R(T::*method)()) { return (object->*method)(); }

};

#endif
