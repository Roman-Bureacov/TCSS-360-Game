//
// Created by iwant on 7/30/2025.
//

#ifndef DUMMY_H
#define DUMMY_H
#include <iostream>

#include "../../../include/AbstractCharacter.h"
#include "../../../include/Bitz.h"

/**
 * Dummy character derived from AbstractCharacter.
 *
 * @author Roman Bureacov
 * @version 2025 July
 */
class Dummy final : public AbstractCharacter {
private:
    const int attackTicks = 3;
    int count = 3;
public:
    Dummy() : AbstractCharacter("Dummy", 25, 0) {
        std::cout << "I, the dummy, have been CONSTRUCTED into existance!" << std::endl;
    }

    ~Dummy() override {
        std::cout << "I, the dummy, have been deconstructed!" << std::endl;
    };

    void attack() override {
        count = attackTicks;
        Bitz::enqueueEvent(
            new Event (
                attackTicks,
                [this]() -> void {
                    std::cout << "HAHAH I AM DUMMY!!! AND I COUNT " << count-- << std::endl;
                },
                *this
            )
        );
    };
};



#endif //DUMMY_H
