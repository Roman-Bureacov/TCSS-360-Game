//
// Created by Riley on 7/22/25.
//
#pragma once

#include <list>
#include <memory>

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
    /* Professor GPT doesn't like this approach, book does though.
     * Should ask tom if std::list<Observer*> *_observers;
     * is better than std::list<Observer*> _observers;
     */
    std::list<Observer *> *_observers;
};

