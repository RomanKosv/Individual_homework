#include "bintree.h"
#include "utils.h"
#include "bintree.h"

template<ordable T>
using branch = BinTree<T> *;

template<comporable T>
BinTree<T>::BinTree(T root_){
    root = root_;
}

template<comporable T>
BinTree<T>::BinTree(T root_, branch<T> left_, branch<T> right_){
    root = root_;
    left = left_;
    right = right_;
    height = max(left_->height, right->height);
}

template<comporable T>
void BinTree<T>::rightRotate(){
    right = new BinTree(root, left->right, right);
    auto left_left = left->left;
    delete left;
    left = left_left;
    height = max(left->height, right->height);
}
