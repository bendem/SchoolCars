#ifndef ARRAYUTILS_HPP
#define ARRAYUTILS_HPP

class ArrayUtils {

public:
    template<class T>
    static void copy(T* dest, const T* src, int size) {
        for(int i = 0; i < size; ++i) {
            dest[i] = T(src[i]);
        }
    }

    template<class T>
    static void fill(T* array, T value, int size) {
        for(int i = 0; i < size; ++i) {
            array[i] = value;
        }
    }

};

#endif
