#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <iostream>
#include "utils.h"

using namespace std;

class DateTime {
public:
    long long year;
    long long mounth;
    long long day;
    long long hour;
    long long minute;
    bool operator <= (DateTime other) {
        return (year < other.year || (year == other.year
                && (mounth < other.mounth || (mounth == other.mounth
                && (day <other.day || (day == other.day
                && (hour < other.hour || (hour == other.hour
                && (minute <= other.minute)))))))));
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

#endif // TASKS_H
