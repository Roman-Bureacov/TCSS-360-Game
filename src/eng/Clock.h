//
// Created by iwant on 7/26/2025.
//

#ifndef CLOCK_H
#define CLOCK_H

class Clock {
private:
    bool isEnabled = false;
    long tickRate = 200;
    long tickCount = 0;

    void tick();
public:
    /**
     * Get a timestamp for time comparisons
     * @return time since epoch in milliseconds
     */
    long getTimestamp();

    /**
     * Gets the current tick count.
     * @return the current tick count
     */
    long getCurrentTick();

    /**
     * Queries if the clock is running.
     * @return if the clock is actively ticking
     */
    bool isActive();

    /**
     * Sets the clock state.
     * @param theState the new state of the clock
     */
    void setActive(bool theState);

    /**
     * Toggles the clock state.
     */
    void toggleActive();
};

#endif //CLOCK_H
