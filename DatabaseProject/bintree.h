#ifndef BINTREE_H
#define BINTREE_H

#include "utils.h"
#include <iostream>

using namespace std;

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
            std::cout<<"init tree\n";
            root = root_;
            left=nullptr;
            right = nullptr;
            height = 1;
        }
        void updateHeight(){
            int l = 0, r =0;
            if (left!=nullptr) l = left->height;
            if (right!=nullptr) r = right->height;
            height = max(l, r)+1;
        }
        void add(T obj){
            if (root <= obj){
                if (right == nullptr) right = new BinTree(obj);
                else right->add(obj);
            }
            else{
                if (left == nullptr) left = new BinTree(obj);
                else left->add(obj);
            }
            balance();
            updateHeight();
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
                updateHeight();
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
                updateHeight();
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
            updateHeight();
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
            root = left->root;
            delete left;
            left = left_left;
            updateHeight();
        }
        void leftRotate(){
            left = new BinTree(root, left, right->left);
            branch right_right = right->right;
            root = right->root;
            delete right;
            right = right_right;
            updateHeight();
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
    void add(T obj){
        if (tree == nullptr) {
            tree = new BinTree(obj);
        }
        else{
            tree->add(obj);
            size_++;
        }
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
    static void pr(BinTree *tr, int tabs){
        if (tr == nullptr) {
            for(int i = 0; i<tabs; i++) std::cout<<'\t';
            std::cout << "nullptr\n";
        }
        else {
            pr(tr->left, tabs+1);
            for(int i = 0; i<tabs; i++) std::cout<<'\t';
            std::cout <<tr->root<<"{height="<<tr->height<<"}:\n";
            pr(tr->right, tabs+1);
        }
    };
    static void print(SortedSet<T> &set){
        int tabs = 0;
        cout<<"Tree:\n";
        pr(set.tree, tabs);
    }
    static void foreach(void fun(T*), BinTree* tr){
        if (tr != nullptr){
            foreach(fun, tr->left);
            fun(&(tr->root));
            foreach(fun, tr->right);
        }
    }
    void foreach(void fun(T*)){
        foreach(fun, tree);
    }
private:
    BinTree *tree;
    int size_;
};

#endif // BINTREE_H
