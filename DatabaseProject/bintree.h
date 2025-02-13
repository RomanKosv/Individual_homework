#ifndef BINTREE_H
#define BINTREE_H

#include "utils.h"

template <comporable T>
class BinTree
{
public:
    BinTree(T root);
    bool add(T obj);
    bool remove(T obj);
    int size();
private:
    BinTree(T root, BinTree<T> *left, BinTree<T> *right);
    BinTree<T> *left;
    BinTree<T> *right;
    void rightRotate();
    void leftRotate();
    void balance();
    T root;
    int height;
};

#endif // BINTREE_H
