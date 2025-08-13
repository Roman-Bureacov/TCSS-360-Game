//
// Created by Riley on 7/22/25.
//
#pragma once

#include <list>
#include <memory>
#include <string>

class Subject;

/**
 * Class that observes changes. This class will await any
 * changes from a subject and respond accordingly.
 * @version 2025 August
 * @author Riley Hopper
 * @author Roman Bureacov
 */

class Observer {
public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject, const std::string& thePropertyName) = 0;

protected:
    Observer();
};

/**
 * Class that notifies any observers for changes.
 * @version August 2025
 * @author Riley Hopper
 * @author Roman Bureacov
 */
class Subject {
public:
    virtual ~Subject();
    virtual void attach(std::unique_ptr<Observer> theObserver);
    virtual void detach(std::unique_ptr<Observer> theObserver);
    virtual void notify(const std::string& thePropertyName);
protected:
    Subject();
private:
    std::list<Observer *> _observers;
};
