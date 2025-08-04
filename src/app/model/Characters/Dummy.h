//
// Created by iwant on 7/30/2025.
//

#ifndef DUMMY_H
#define DUMMY_H
#include <iostream>

#include "Dummy.h"
#include "../../../include/AbstractCharacter.h"
#include "../../../include/Bitz.h"


class DummyWeapon : public Weapon {
private:

public:
    /**
     * Creates a dummy weapon with 10 damage, 1 attack tick, and a 10x10 hitbox
     */
    DummyWeapon()
    : Weapon(
        10,
        1,
        Hitbox(10, 10)
    ) { }

};


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
        giveWeapon(new DummyWeapon());
    }

    ~Dummy() override {
        std::cout << "I, the dummy, have been deconstructed!" << std::endl;
    }

    void attack() {

        Bitz::enqueueAttackEvent(this);

    }
};




#endif //DUMMY_H
