
#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <concepts>

template<typename T>
concept ordable = requires (T a, T b){
    a <= b;
    {a <= b} -> std::same_as<bool>;
};


#endif // DATA_BASE_H
