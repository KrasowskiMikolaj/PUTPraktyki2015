//CPP File
#include "../../include/Visualizer/observer.h"
#include <algorithm>
#include <iostream>

using namespace std;

void Subject::attach(Observer *observer){
    list.push_back(observer);
}
void Subject::detach(Observer *observer){
    list.erase(std::remove(list.begin(), list.end(), observer), list.end());
}

void Subject::notify(std::vector<simulator::Mat34>& envState){
    for(vector<Observer*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        if(*iter != 0) {
            (*iter)->update(envState);
        }
    }
}
