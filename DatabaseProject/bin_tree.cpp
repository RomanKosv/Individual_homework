#include "data_base.h"
#include <assert.h>

using namespace std;

template<ordable T, bool isRight = true>
struct BinTree{
    BinTree(T root_){
        root = root_;
    }
private:
    T root;
    BinTree* left=nullptr;
    BinTree* right=nullptr;
    int height;
};
