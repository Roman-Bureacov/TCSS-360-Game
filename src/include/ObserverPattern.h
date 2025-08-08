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

    virtual void Update(std::unique_ptr<Subject> subject);

protected:
    Observer();
};

class Subject {
public:
    virtual ~Subject();
    virtual void attach(std::unique_ptr<Observer>);
    virtual void detach(std::unique_ptr<Observer>);
    virtual void notify();
protected:
    Subject();
private:
    /* Professor GPT doesn't like this approach, book does though.
     * Should ask tom if std::list<Observer*> *_observers;
     * is better than std::list<Observer*> _observers;
     */
    std::list<std::unique_ptr<Observer>> _observers;
};

