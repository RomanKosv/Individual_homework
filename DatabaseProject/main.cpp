#include <iostream>
#include "array_utils.h"
#include "linkedlist.h"
#include "bintree.h"
#include "tasks.h"

using namespace std;

static nevector<Task> arr;

template<comporable T>
class Index {
public:
    int index;
    virtual T key(Task t);
    bool operator <=(Index<T> &other){
        return key(arr[index]) <= other.key(arr[other.index]);
    }
    bool operator ==(Index<T> &other){
        return key(arr[index]) == other.key(arr[other.index]);
    }
};

struct DeadlineIndex : Index<DateTime>{
    DateTime key(Task t) override {
        return t.deadline;
    }
};

struct ImportanceIndex : Index<double> {
    double key(Task t) override {
        return t.importance;
    }
};

int main()
{
    for(int i = 0; i < 20; i++){

    }
}
