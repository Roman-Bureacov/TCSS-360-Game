//
// Created by iwant on 7/26/2025.
//

#include "../include/Clock.h"
#include "../include/Bitz.h"
#include <chrono>
#include <iostream>

long Clock::getTimestamp() {
    // TODO: what here???
    return 0;
}

long Clock::getCurrentTick() {
    return tickCount;
}

void Clock::tick() {

}

void Clock::runClock() {
    while (isActive()) {

        Bitz::processEvents();
        tickCount++;

        std::this_thread::sleep_for(std::chrono::milliseconds(tickRate));

    }
}

bool Clock::isActive() {
    return isEnabled;
}

void Clock::setActive(const bool theState) {
    isEnabled = theState;
}

void Clock::toggleActive() {
    isEnabled = !isEnabled;
}
