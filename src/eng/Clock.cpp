//
// Created by iwant on 7/26/2025.
//


#include "../include/Clock.h"

class Bitz;

void Clock::resetClock() {
    isEnabled = false;
    tickCount = 0;
}

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
    setActive(true);
    while (isActive()) {
        //This will stop the clock for testing.
        if (testingStopTick != 0 && testingStopTick <= tickCount) break;
        /*if (!View::guiInstance()->getRunning()) {
            std::cout << View::guiInstance()->getRunning() << std::endl;
            break;
        }*/

        SDL_Event gameEvent = { 0 };
        View::guiInstance()->handleEvent(gameEvent);

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

void Clock::StopClockForTesting( const long theStopTick) {
    testingStopTick = theStopTick + getCurrentTick();
}
