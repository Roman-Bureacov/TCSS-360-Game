//
// Created by Riley on 7/22/25.
//
#pragma once

#include <list>

class Subject;



class Observer {
public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;

protected:
    Observer();
};

class Subject {
public:
    virtual ~Subject();
    virtual void attach(Observer*);
    virtual void detach(Observer*);
    virtual void notify();
protected:
    Subject();
private:
    std::list<Observer*> _observers;
};

