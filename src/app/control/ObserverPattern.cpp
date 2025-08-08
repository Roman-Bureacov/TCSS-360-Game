//
// Created by Riley on 7/22/25.
//
#include "../../include/ObserverPattern.h"


Observer::Observer() = default;
Observer::~Observer() = default;

void Observer::Update(std::unique_ptr<Subject> subject) {
}

Subject::Subject() = default;
Subject::~Subject() = default;


void Subject::attach(const std::unique_ptr<Observer> theObserver) {
    _observers.push_back(theObserver);
}
void Subject::detach(const std::unique_ptr<Observer> theObserver) {
    _observers.remove(theObserver);
}
void Subject::notify() {

    //Uses an interator to go through the list of observers.
    for (auto it = _observers.begin()
        ; it != _observers.end(); ++it) {
        (*it)->Update(std::unique_ptr<Subject>(this));
    }
}


