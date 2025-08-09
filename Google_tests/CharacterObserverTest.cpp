//
// Created by iwant on 8/8/2025.
// This tests the observer design pattern on the characters
//

#include "../src/app/model/Characters/Dummy.h"
#include "gtest/gtest.h"

/**
 * Derivative of the dummy class for testing purposes.
 * Has a state that can changed based on what happens to the first dummy
 */
class DerivativeDummy : public Dummy {
public:
    int state = 0;

    void Update(Subject *theChangedSubject, const std::string &thePropertyName) override {
        if (thePropertyName == PROPERTY_DAMAGED) state = 1;
        else if (thePropertyName == PROPERTY_HEALED) state = 2;
        else if (thePropertyName == PROPERTY_HEALTH_CHANGED) state = 3;
        else if (thePropertyName == PROPERTY_MAX_HEALTH_CHANGED) state = 4;
        else if (thePropertyName == PROPERTY_KILLED) state = 5;
        else if (thePropertyName == PROPERTY_LOCATION_CHANGED) state = 6;
        else if (thePropertyName == PROPERTY_MVMT_CHANGED) state = 7;
        else if (thePropertyName == PROPERTY_BASE_MVMT_CHANGED) state = 8;
        else if (thePropertyName == PROPERTY_WEAPON_CHANGED) state = 9;
        else if (thePropertyName == PROPERTY_HITBOX_CHANGED) state = 10;
        else if (thePropertyName == PROPERTY_DIRECTION_CHANGED) state = 11;
    }
};

/**
 * Tests if the observer pattern is functioning properly on the character class.
 */
class ObserverTest : public ::testing::Test {
protected:
    Dummy *d1 = new Dummy();
    DerivativeDummy *d2 = new DerivativeDummy();

    void SetUp() override {
        d1->attach(d2);
    }

    void TearDown() override {
        delete d1;
        delete d2;
    }
};

TEST_F(ObserverTest, CharacterDamaged) {
    d1->setMaxHealth(1000);
    ASSERT_EQ(d2->state, 4);
    d1->setHealth(d1->getMaxHealth());
    ASSERT_EQ(d2->state, 3);
    d1->heal(10);
    ASSERT_EQ(d2->state, 2);
    d1->damage(20);
    ASSERT_EQ(d2->state, 1);
    d1->setX(5);
    ASSERT_EQ(d2->state, 6);
    d2->state = 0;
    d1->setY(5);
    ASSERT_EQ(d2->state, 6);
    d1->setBaseMovementSpeed(6);
    ASSERT_EQ(d2->state, 8);
    d1->setMovementSpeed(6);
    ASSERT_EQ(d2->state, 7);

    d1->setHealth(0);
    ASSERT_EQ(d2->state, 5);
    d1->setHealth(10);
    d2->state = 0;
    d1->damage(20);
    ASSERT_EQ(d2->state, 5);

    d1->giveWeapon(nullptr);
    ASSERT_EQ(d2->state, 9);

    d1->setHitbox(1, 1);
    ASSERT_EQ(d2->state, 10);

    d1->setDirection(util::NORTH);
    ASSERT_EQ(d2->state, 11);
}