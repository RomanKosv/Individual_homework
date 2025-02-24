#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <iostream>
#include "utils.h"
#include "array_utils.h"

using namespace std;

class DateTime {
public:
    long long year;
    long long mounth;
    long long day;
    long long hour;
    long long minute;
    bool operator <= (DateTime other) {
        return tie(year, mounth, day, hour, minute) <= tie(other.year, other.mounth, other.day, other.hour, other.minute);
    }
    bool operator == (DateTime other) {
        return tie(year, mounth, day, hour, minute) == tie(other.year, other.mounth, other.day, other.hour, other.minute);
    }
};

struct Task {
public:
    int time_minutes;
    DateTime deadline;
    double importance;
    string description;
    static Task input(){
        Task task;
        cin>>task.description;
        cin>>task.importance;
        cin
            >>task.deadline.year
            >>task.deadline.mounth
            >>task.deadline.day
            >>task.deadline.hour
            >>task.deadline.minute;
        cin>>task.time_minutes;
        return task;
    }
    void print(){
        cout<<"description: "<<description<<'\n';
        cout<<"importance: "<<importance<<'\n';
        cout<<"deadline:\n";
        cout<<"\tyear: "<<deadline.year<<"\n";
        cout<<"\tmounth: "<<deadline.mounth<<'\n';
        cout<<"\tday: "<<deadline.day<<'\n';
        cout<<"\thour: "<<deadline.hour<<'\n';
        cout<<"\tminute: "<<deadline.minute<<'\n';
        cout<<"time in minutes to solve: "<<time_minutes<<'\n';
    }
};

static nevector<Task> arr{};

template<comporable T>
class Index {
public:
    int index;
    Index() {
        index = -1;
    }
    Index(int ind) {
        index = ind;
    }
    virtual T key(Task& t)=0;
    bool operator <=(Index<T> &other){
        return key(arr[index]) <= other.key(arr[other.index]);
    }
    bool operator ==(Index<T> &other){
        return key(arr[index]) == other.key(arr[other.index]);
    }
    bool operator <(Index<T> &other){
        return (*this)<=other && !((*this)==other);
    }
    void print(){
        cout<<"element number "<<index<<":\n";
        arr[index].print();
    }
};
template<comporable T>
ostream& operator <<(ostream& os, Index<T>& ind){
    return os<<ind.index;
}

#endif // TASKS_H
