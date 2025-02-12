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
    void leftRotate();
    void rightRotate();
    BinTree<T> *left;
    BinTree<T> *right;
    T root;
    int height;
};

#endif // BINTREE_H
