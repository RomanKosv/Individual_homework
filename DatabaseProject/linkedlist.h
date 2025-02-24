#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "utils.h"
#include <iostream>

using namespace std;

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
        static void recursionFind(Node* node, T obj, void fun(Node*)) {
            if (node == nullptr) return;
            else if (node->object == obj) fun(node);
            else if (node->object <= obj) recursionFind(node->next, obj, fun);
            else return;
        }
        static void iterationFind(Node* node, T obj, void fun(Node*)) {
            while (true) {
                if (node == nullptr) return;
                else if (node->object == obj) fun(node);
                else if (node->object <= obj) node = node ->next;
                else return;
            }
        }
    };
    void findall_iterative(T obj, void fun(T*)) {
        Node::iterationFind(first, obj, [&fun](Node* nd) {
            fun(&(nd->object));
        });
    }
    void findall_recursive(T obj, void fun(T*)) {
        Node::recursionFind(first, obj, [&fun](Node* nd) {
            fun(&(nd->object));
        });
    }
    void delete_all(T obj) {

    }
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
    static void print(LinkedList<T,sorted> &list) {
        Node *current = list.first;
        cout << '[';
        while (current != nullptr) {
            cout << current->object<<" ;";
            current = current->next;
        }
        cout << "]\n";
    }
    void foreach( void fun(T*)){
        Node *current = first;
        while (current != nullptr) {
            fun(&(current->object));
            current = current->next;
        }
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
        while (! (*current == nullptr || obj <= (*current)->object)) current = &((*current)->next);
        *current = new Node(obj, *current);
    }
};

#endif // LINKEDLIST_H
