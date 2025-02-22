#ifndef BINTREE_H
#define BINTREE_H

#include "utils.h"




template<comporable T>
class SortedSet{
public:
    SortedSet(){
        tree = nullptr;
        size_ = 0;
    }
    struct BinTree
    {
        using branch = BinTree *;
    public:
        BinTree(T root_) {
            root = root_;
        }
        void add(T obj){
            if (root <= obj){
                right ->add(obj);
            }
            else{
                left->add(obj);
            }
            balance();
        }
        bool remove(T obj){
            if (obj == root) {
                if (right == nullptr){
                    branch old_left = left;
                    left = old_left->left;
                    right = old_left->right;
                    root = old_left->root;
                    delete old_left;
                }
                else {
                    branch current = right;
                    while (current->left != nullptr) current = current->left;
                    root = current->root;
                    right->remove(root);
                    balance();
                }
                return true;
            }
            else{
                bool removed;
                if (root <= obj){
                    removed = right->remove(obj);
                }
                else{
                    removed = left->remove(obj);
                }
                balance();
                return removed;
            }
        }
        int size(){
            int l,r;
            if (left == nullptr) l = 0;
            else l = left->size();
            if (right == nullptr) r = 0;
            else r  = right->size();
            return l+r+1;
        }
        BinTree(T root_, branch left_, branch right_){
            root = root_;
            left = left_;
            right = right_;
            height = max(left_->height, right->height);
        }
        BinTree *left;
        BinTree *right;
        int getBalance(){
            int l,r;
            if (left == nullptr) l = 0;
            else l = left->height;
            if (right == nullptr) r = 0;
            else r  = right->height;
            return r-l;
        }
        T root;
        int height;
        void freeTree(){
            if (left != nullptr) {
                left->freeTree();
                delete left;
            }
            if (right != nullptr) {
                right->freeTree();
                delete right;
            }
            height = 0;
        }
    private:
        void rightRotate(){
            right = new BinTree(root, left->right, right);
            branch left_left = left->left;
            delete left;
            left = left_left;
            height = max(left->height, right->height);
        }
        void leftRotate(){
            left = new BinTree(root, left, right->left);
            branch right_right = right->right;
            delete right;
            right = right_right;
            height = max(left->height, right->height);
        }
        void balance(){
            int delta = getBalance();
            if (delta < -1){
                if (left->getBalance() > 0){
                    left->leftRotate();
                }
                rightRotate();
            }
            else if (delta > 1){
                if (right->getBalance() < 0){
                    right->rightRotate();
                }
                leftRotate();
            }
        }
    };
    bool add(T obj){
        if (tree == nullptr) {
            tree = new BinTree(obj);
            return true;
        }
        else if (tree->add(obj)){
            size_++;
            return true;
        }
        else return false;
    }
    bool remove(T obj){
        if (tree == nullptr) {
            return false;
        }
        else if (tree->remove(obj)){
            size_--;
            return true;
        }
        else return false;
    }
    int size(){
        return size_;
    }
    ~SortedSet(){
        tree->freeTree();
        delete tree;
    }
private:
    BinTree *tree;
    int size_;
};

#endif // BINTREE_H
