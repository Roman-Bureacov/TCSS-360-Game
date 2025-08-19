//
// Created by iwant on 7/26/2025.
//

#include "../include/Clock.h"
#include "../include/Bitz.h"
#include "../include/NPC.h"

#include <chrono>
#include <iostream>
#include <thread>


long Clock::getTickRate() {
    return tickRate;
}

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

        //Placeholder for now, till we have a better way
        //To poke the active NPCs
        for (auto character : Bitz::getEntities()) {
            auto npc = std::dynamic_pointer_cast<NPC>(character);
            if (npc && npc->getIsActive()) {
                npc->takeAction();
            }
        }

        Bitz::processEvents();
        tickCount++;

        std::this_thread::sleep_for(std::chrono::milliseconds(tickRate));


        //This will stop the clock for testing.
        if (testingStopTime != 0 && testingStopTime > tickCount) {

            break;
        }

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

void Clock::StopClockForTesting(long stopTime) {
    testingStopTime = Clock::getTimestamp() + stopTime;
}
