//
// Created by iwant on 8/1/2025.
//

#ifndef ID_GEN_H
#define ID_GEN_H

#include <chrono>

/**
 * Static class that provides unique IDs as longs using the system time.
 * @author Roman Bureacov
 * @version August 2025
 */
class ID_GEN {
private:
    static std::mutex idMutex; // lock the thread, preventing possible ID collisions

public:
    /**
     * Generates a unique ID based on the system time.
     * @return an ID in the form of a long long as the current time in microseconds since epoch.
     */
    static unsigned long long makeID() {
        std::lock_guard lock(idMutex);
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeSinceEpoch = currentTime.time_since_epoch();

        return std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch).count();
    }

};

#endif //ID_GEN_H
