#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "data_base.h"

template<ordable T>
struct BinTree{
    BinTree(T root);
    bool add(T* obj);
    bool remove(T& obj);
};

#endif // BIN_TREE_H
