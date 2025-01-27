#include "data_base.h"
#include <assert.h>

using namespace std;

template<ordable T, bool isRight = true>
struct BinTree{
    BinTree(T root_){
        root = root_;
    }
    //work wrong if new tree will not be invriant
    void leftRotation(){
        left = new BinTree{root, left, right->left, left->height + 1};
        root = right->root;
        auto right_ = right;
        right = right->right;
    }
    //work wrong if new tree will not be invriant
    void rightRotation(){
        right = new BinTree{root, left->right, right, right->height + 1};
        root = left->root;
        auto left_ = left;
        left = left->left;
        delete left_;
    }
    bool add(T element){
        if (root < element){
            //add right
            bool is_add = right->add(element);
            if (is_add && (isRight && right->height - left->height > 1 || !isRight && right->height - left->height > 0)){
                leftRotation();
            }
            return is_add;
        }
        else if (element < root){
            //add left
            bool is_add = left->add(element);
            if (is_add && (!isRight && left->height - right->height > 1 || isRight && left->height - right->height > 0)){
                rightRotation();
            }
            return is_add;
        }
        else return false; //no add
    }
    bool remove(T element){
        if (element < root){
            //remove left
            bool succes = left->remove(element);

        }
        else if (root < element){
            //remove right
        }
        else return false; //no remove
    }
private:
    T root;
    BinTree* left=nullptr;
    BinTree* right=nullptr;
    int height;
};
