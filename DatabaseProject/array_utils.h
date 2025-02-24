#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H
#include<assert.h>
template<typename T>
class nevector{
private:
    int ln;
    T *array;
public:
    nevector(int size){
        assert(size>0);
        array=new T[size];
        this->ln=size;
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
    ~nevector(){
        delete [] array;
    }
};
template<typename T, typename Predicate>
nevector<T> merge(nevector<T> a, nevector<T> b, Predicate less) {
    int i1 = 0, i2 = 0;
    nevector<T> res(a.size() + b.size());
    for (int ind = 0; ind < res.size(); ind++) {
        if (i1 < a.size() && (i2 >= b.size() || less(a[i1], b[i2]))) {
            res[ind] = a[i1];
            i1++;
        }
        else {
            res[ind] = b[i2];
            i2++;
        };
    }
    return res;
}
template<typename T, typename Predicate>
nevector<T> merge_sort(nevector<T> vec, Predicate less) {
    if (vec.size() <= 1) {
        return vec;
    }
    nevector<T> a(vec.size() / 2), b((vec.size() + 1) / 2);
    for (int i = 0;i < vec.size();i++) {
        if (i % 2 == 0)
            b[i] = vec[i];
        else
            a[i] = vec[i];
    }
    return merge(merge_sort(a, less), merge_sort(b, less), less);
}
template<typename T, typename Predicate>
void swap_sort(nevector<T> vec, Predicate less){
    for(int i=0; i<vec.size(); i++){
        for(int j=i+1; j<vec.size(); j++){
            if(!less(vec[i],vec[j])){
                tie(vec[i],vec[j])=(vec[j],vec[i]);
            }
        }
    }
}
template<typename T, typename Sort>
nevector<int> SortIndsBy(nevector<T> vec, bool comp(T, T), Sort sort_on_place) {
    nevector<int> inds(vec.size());
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
