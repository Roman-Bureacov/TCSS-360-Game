//
// Created by Riley on 7/22/25.
//
#include "ObserverPattern.h"


Observer::Observer() = default;
Observer::~Observer() = default;

Subject::Subject() = default;
Subject::~Subject() = default;


void Subject::attach(Observer* theObserver) {
    _observers.push_back(theObserver);
}
void Subject::detach(Observer* theObserver) {
    _observers.remove(theObserver);
}
void Subject::notify() {

    //Uses an interator to go through the list of observers.
    for (auto it = _observers.begin()
        ; it != _observers.end(); ++it) {
        (*it)->Update(this);
    }
}


