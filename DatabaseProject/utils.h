#ifndef UTILS_H
#define UTILS_H

template<typename T>
concept ordable = requires (T a, T b){
    bool {a <= b};
};

template<typename T>
concept comporable = requires (T a, T b){
    bool {a==b};
    {a}->ordable;
};

template<ordable T>
T max(T first, T rest...){
    T max_rest= max(rest);
    if (max_rest<=first){
        return first;
    }
    else{
        return max_rest;
    }
}

template<ordable T>
T max(T one){
    return one;
}

#endif // UTILS_H
