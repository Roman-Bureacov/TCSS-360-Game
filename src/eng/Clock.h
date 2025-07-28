//
// Created by iwant on 7/26/2025.
//

#ifndef CLOCK_H
#define CLOCK_H

/**
 * Static class that handles timekeeping and ticks the engine at specific intervals
 * to process events.
 * @author Roman Bureacov
 * @version 2025 July
 */
class Clock {
private:
    inline static bool isEnabled = false;
    inline static long tickRate = 200;
    inline static long tickCount = 0;

    static void tick();
    static void runClock();

    Clock() = delete;
public:
    /**
     * Get a timestamp for time comparisons
     * @return time since epoch in milliseconds
     */
    static long getTimestamp();

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
};

#endif //CLOCK_H
