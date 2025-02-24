#include <iostream>
#include "array_utils.h"
#include "linkedlist.h"
#include "bintree.h"
#include "tasks.h"

using namespace std;

class DeadlineIndex :public Index<DateTime>{
public:
    DeadlineIndex() {}
    DeadlineIndex(int ind) : Index(ind){}
    DateTime key(Task &t) override {
        return t.deadline;
    }
};

class ImportanceIndex : public Index<double> {
public:
    ImportanceIndex() {}
    ImportanceIndex(int ind) : Index(ind){}
    double key(Task &t) override {
        return t.importance;
    }
};
template<typename Iter, typename Index>
void print_index(Iter &iter){
    cout<<"Index:\n";
    iter.foreach([](Index *ind) {
        ind->print();
        cout << "--------------\n";
    });
}

LinkedList<DeadlineIndex, true> deadline_list{};
LinkedList<ImportanceIndex, true> importance_list{};
SortedSet<DeadlineIndex> deadline_tree{};
SortedSet<ImportanceIndex> importance_tree{};
nevector<DeadlineIndex> deadline_array{};
nevector<ImportanceIndex> importance_array{};

void shadow(int index) {
    assert(index < arr.size());
    assert(index >=0);
    arr[index].shadow=true;
}
void change(int index, Task newval) {
    assert(index < arr.size());
    assert(index >=0);
    arr[index] = newval;
    merge_sort(deadline_array, [](DeadlineIndex& a,DeadlineIndex& b){return a<b;});
    merge_sort(importance_array, [](ImportanceIndex& a,ImportanceIndex& b){return a<b;});
    deadline_tree = SortedSet<DeadlineIndex>{};
    importance_tree = SortedSet<ImportanceIndex>{};
    deadline_list = LinkedList<DeadlineIndex, true>{};
    importance_list = LinkedList<ImportanceIndex, true>{};
    for(int i = 0; i< arr.size(); i++){
        deadline_list.add(DeadlineIndex(i));
        //deadline_array.print();
        //importance_array.print();
        //LinkedList<DeadlineIndex,true>::print(deadline_list);
        importance_list.add(ImportanceIndex(i));
        //LinkedList<ImportanceIndex,true>::print(importance_list);
        deadline_tree.add(DeadlineIndex(i));
        //SortedSet<DeadlineIndex>::print(deadline_tree);
        importance_tree.add(ImportanceIndex(i));
    }
}
int main()
{
    while (true) {
        string command;
        cin >> command;
        if (command == "print") {
            string mode;
            cin >> mode;
            if (mode == "all") {
                for(int i = 0; i < arr.size(); i++) {
                    arr[i].print();
                    cout << "-------------\n";
                }
            }
            else if (mode == "deadline tree") {
                print_index<SortedSet<DeadlineIndex>,DeadlineIndex>(deadline_tree);
            }
            else if (mode == "importance tree") {
                print_index<SortedSet<ImportanceIndex>,ImportanceIndex>(importance_tree);
            }
            else if (mode == "deadline list") {
                print_index<LinkedList<DeadlineIndex, true>,DeadlineIndex>(deadline_list);
            }
            else if (mode == "importance list") {
                print_index<LinkedList<ImportanceIndex, true>,ImportanceIndex>(importance_list);
            }
            else if (mode == "deadline array") {
                print_index<nevector<DeadlineIndex>,DeadlineIndex>(deadline_array);
            }
            else if (mode == "importance array") {
                print_index<nevector<ImportanceIndex>,ImportanceIndex>(importance_array);
            }
            else cout << "it is not valid print mode";
        }
        else if (command == "add") {
            int i = arr.size();
            arr.push(Task::input());
            deadline_array.push(DeadlineIndex(i));
            swap_sort(deadline_array, [](DeadlineIndex& a,DeadlineIndex& b){return a<b;});
            importance_array.push(ImportanceIndex(i));
            swap_sort(importance_array, [](ImportanceIndex& a, ImportanceIndex& b) {return a<b;});
            deadline_list.add(DeadlineIndex(i));
            //deadline_array.print();
            //importance_array.print();
            //LinkedList<DeadlineIndex,true>::print(deadline_list);
            importance_list.add(ImportanceIndex(i));
            //LinkedList<ImportanceIndex,true>::print(importance_list);
            deadline_tree.add(DeadlineIndex(i));
            //SortedSet<DeadlineIndex>::print(deadline_tree);
            importance_tree.add(ImportanceIndex(i));
        }
        else if (command == "stop") {
            break;
        }
    }
}
