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
    virtual T key();

};

struct DeadlineIndex {
    int index;
    bool operator <=(DeadlineIndex& other) {
        return arr[index].deadline <= arr[other.index].deadline;
    }
    bool operator ==(DeadlineIndex& other) {
        return arr[index].deadline == arr[other.index].deadline;
    }
};

int main()
{

}
