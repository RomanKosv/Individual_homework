#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "utils.h"

template<comporable T, bool sorted=false>
class LinkedList{
public:
    struct Node{
        Node *next = nullptr;
        T object;
        Node(T obj){
            object = obj;
        }
        Node(T obj, Node *rest) : Node(obj) {
            next = rest;
        }
        static void freeAll(Node * node){
            if (node != nullptr) {
                freeAll(node->next);
                delete node;
            }
        }
        static bool deleteFound(Node **node, bool check(T)){
            if (*node == nullptr) return false;
            else if (check((*node)->object)) {
                delete *node;
                *node = (*node)->next;
                return true;
            }
            else return deleteFound(&((*node)->next), check);
        }
        static Node* recursionFind(Node* node, T obj) {
            if (node == nullptr || (sorted && !(obj <= node->object))) return nullptr;
            else if (node->object == obj) return node;
            else return recursionFind(node->next, obj);
        }
        static Node* iterationFind(Node* node, T obj) {
            while (true) {
                if (node == nullptr || (sorted && !(obj <= node->object))) return nullptr;
                else if (node->object == obj) return node;
                else node = node->next;
            }
        }
    };
    void add(T obj){
        if (sorted) addSorted(obj);
        else addLast(obj);
    }
    bool deleteFound(bool check(T)) {
        return Node::deleteFound(&first, check);
    }
    ~LinkedList(){
        Node::freeAll(first);
    }

private:
    Node *first;
    void addFirst(T obj) {
        first = new Node(obj, first);
    }
    void addLast(T obj){
        Node **current = &first;
        while (*current != nullptr) current = &((*current)->next);
        *current = new Node(obj);
    }
    void addSorted(T obj) {
        Node **current = &first;
        while (! (*current != nullptr || obj <= (*current)->object)) current = &((*current)->next);
        *current = new Node(obj, *current);
    }
};

#endif // LINKEDLIST_H
