
#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "../include/Defs/defs.h"
#include <vector>
#include <list>

class Observer
{
public:
    virtual void update(std::vector<simulator::Mat34>& envState) = 0;
};

class Subject
{
    //Lets keep a track of all the shops we have observing
    std::vector<Observer*> list;

public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notify(std::vector<simulator::Mat34>& envState);
    void DrawBox(const float sides[3], const float pos[3], const float R[12]);
};

#endif // OBSERVER_H_
