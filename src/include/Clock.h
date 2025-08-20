//
// Created by iwant on 7/26/2025.
//

#ifndef CLOCK_H
#define CLOCK_H



#include "../include/Bitz.h"
#include "../include/NPC.h"
#include "../include/View.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "SDL3/SDL.h"

/**
 * Static class that handles timekeeping and ticks the engine at specific intervals
 * to process events.
 * @author Roman Bureacov
 * @author Riley Hopper
 * @version 2025 July
 */
class Clock {
private:
    inline static bool isEnabled = false;
    inline static long tickRate = 25;
    inline static long tickCount = 0;
    inline static long testingStopTick = 0;

    static void tick();

    Clock() = delete;
public:
    /**
     *
     * @return The tickrate of the clock.
     */
    static long getTickRate();
    /**
     * Get a timestamp for time comparisons
     * @return time since epoch in milliseconds
     */
    static long getTimestamp();

    static void runClock();

    /**
     * Gets the current tick count.
     * @return the current tick count
     */
    static long getCurrentTick();

    /**
     * Queries if the clock is running.
     * @return if the clock is actively ticking
     */
    static bool isActive();

    /**
     * Sets the clock state.
     * @param theState the new state of the clock
     */
    static void setActive(bool theState);

    /**
     * Toggles the clock state.
     */
    static void toggleActive();

    /**
     * This stops the clock at the inputted tick for testing,
     * if 0 clock will not stop.
     * @param stopTick The tick you want the clock to end at
     */
    static void StopClockForTesting(long stopTick);
};

#endif //CLOCK_H
