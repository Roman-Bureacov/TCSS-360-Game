//
// Created by iwant on 7/26/2025.
//

#include "Clock.h";
#include <chrono>;

long Clock::getTimestamp() {

}

bool Clock::isActive() {
    return isEnabled;
}

void Clock::setActive(const bool theState) : isEnabled(theState) { }

void Clock::toggleActive() {
    isEnabled = !isEnabled;
}
