#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H


#include<assert.h>
#include <iostream>

using namespace std;

template<typename T>
class nevector{
private:
    int ln;
    int reserved;
    T *array;
public:
    void print() {
        cout<<'[';
        for(int i = 0; i<ln; i++) cout<<array[i]<<"; ";
        cout << "]\n";
    }
    nevector(int size){
        assert(size>=0);
        ln = size;
        reserved = (ln+1) * 2;
        array=new T[reserved];
    }
    nevector() : nevector(0) {
    }
    int size(){
        return ln;
    }
    T& operator [](int ind){
        assert(ind>=0);
        assert(ind<ln);
        return array[ind];
    }
    void push(T obj) {
        if (ln == reserved) {
            reserved = (ln+1) * 2;
            T *newarr = new T[reserved];
            for(int i = 0; i < ln; i++) {
                newarr[i] = array[i];
            }
            delete[] array;
            array=nullptr;
            array = newarr;
        }
        ln++;
        (*this)[ln-1] = obj;
    }
    void foreach(void fun(T*)) {
        for(int i = 0; i<ln; i++) fun(&(array[i]));
    }
    ~nevector(){
        delete [] array;
    }
};
template<typename T, typename Predicate>
void merge(nevector<T> &out,nevector<T> &a, nevector<T> &b, Predicate less) {
    int i1 = 0, i2 = 0;
    for (int ind = 0; ind < out.size(); ind++) {
        if (i1 < a.size() && (i2 >= b.size() || less(a[i1], b[i2]))) {
            out[ind] = a[i1];
            i1++;
        }
        else {
            out[ind] = b[i2];
            i2++;
        };
    }
}
template<typename T, typename Predicate>
void merge_sort(nevector<T> &vec, Predicate less) {
    if (vec.size() <= 1) {
        return;
    }
    nevector<T> a(vec.size() / 2), b((vec.size() + 1) / 2);
    for (int i = 0;i < vec.size();i++) {
        if (i % 2 == 0)
            b[i/2] = vec[i];
        else
            a[i/2] = vec[i];
    }
    merge_sort(a, less);
    merge_sort(b, less);
    merge(vec, a, b, less);
}
template<typename T, typename Predicate>
void swap_sort(nevector<T> &vec, Predicate less){
    for(int i=0; i<vec.size(); i++){
        for(int j=i+1; j<vec.size(); j++){
            if(!less(vec[i],vec[j])){
                T veci = vec[i];
                vec[i] = vec[j];
                vec[j] = veci;
            }
        }
    }
}
template<typename T, typename Sort>
nevector<int> SortIndsBy(nevector<T> vec, bool comp(T, T), Sort sort_on_place) {
    nevector<int> inds{vec.size()};
    for (int i = 0; i < vec.size(); i++) {
        inds[i] = i;
    }
    sort_on_place(
        &inds,
        [&vec, &comp](int i, int j) {return comp(vec[i], vec[j]);}
        );
    return inds;
}
template<typename Predicate>
int bin_search_iterate_last(int left, int right, Predicate less_or_eq){
    while(right-left>1){
        int mid=(right+left)/2;
        if(less_or_eq(mid)){
            left=mid;
        }else{
            right=mid;
        }
    }
    return left;
}
template<typename Predicate>
int bin_search_req_last(int left, int right, Predicate less_or_eq){
    if(right-left<=1){
        return left;
    }
    else{
        int mid=(right+left)/2;
        if(less_or_eq(mid)){
            left=mid;
        }else{
            right=mid;
        }
        return bin_search_req_last(left,right,less_or_eq);
    }
}

#endif // ARRAY_UTILS_H
