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
    branch<T> left_left = left->left;
    delete left;
    left = left_left;
    height = max(left->height, right->height);
}

template<comporable T>
void BinTree<T>::leftRotate(){
    left = new BinTree(root, left, right->left);
    branch<T> right_right = right->right;
    delete right;
    right = right_right;
    height = max(left->height, right->height);
}

template<comporable T>
void BinTree<T>::balance(){
    int delta = right->height - left->height;
    if (delta < -1){
        if (left->left->height < left->right->height){
            left->leftRotate();
        }
        rightRotate();
    }
    else if (delta > 1){
        if (right->left->height > right->right->height){
            right->rightRotate();
        }
        leftRotate();
    }
}

template<comporable T>
bool BinTree<T>::add(T obj){
    if (obj == root) return true;
    else{
        bool added;
        if (root <= obj){
            added = right ->add(obj);
        }
        else{
            added = left->add(obj);
        }
        balance();
        return added;
    }
}

template<comporable T>
bool BinTree<T>::remove(T obj){
    if (obj == root) {

        return true;
    }
    else{
        bool added;
        if (root <= obj){
            added = right ->add(obj);
        }
        else{
            added = left->add(obj);
        }
        balance();
        return added;
    }
}

