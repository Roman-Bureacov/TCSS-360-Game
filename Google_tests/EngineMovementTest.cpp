//
// Created by iwant on 8/18/2025.
//


#include "../src/app/model/Characters/Dummy.h"
#include "../src/include/Clock.h"
#include "gtest/gtest.h"

class EngineMovementTest : public testing::Test {
protected:
    AbstractCharacter* d1;
    AbstractCharacter* d2;
    Hitbox* hb;

    void SetUp() override {
        d1 = new Dummy();
        d2 = new Dummy();

        hb = new Hitbox(10, 10);
        d1->setHitbox(*hb);
        d2->setHitbox(*hb);
    }

    /**
     * Convenience method for returning an event that stops the clock.
     * @return an event that stops the clock
     */
    Event* getStopClockEvent() {
        return new Event(
            1,
            []() -> void {
                Clock::setActive(false);
            },
            *d2);
    }
};

TEST_F(EngineMovementTest, MovementTestNorth) {

    d1->setX(0); d1->setY(0);
    d2->setX(0); d2->setY(50);

    d1->setDirection(util::NORTH);

    // no collision problems should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 0);
    EXPECT_EQ(d1->getY(), 25);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 0);
    EXPECT_EQ(d1->getY(), 50 - hb->getHeight());

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 50 - hb->getHeight());
    EXPECT_EQ(d1->getY(), 0);
}

TEST_F(EngineMovementTest, MovementTestEast) {

    d1->setX(0); d1->setY(0);
    d2->setX(50); d2->setY(0);

    d1->setDirection(util::EAST);

    // no collision problems should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 25);
    EXPECT_EQ(d1->getY(), 0);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 50 - hb->getWidth());
    EXPECT_EQ(d1->getY(), 0);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 50 - hb->getWidth());
    EXPECT_EQ(d1->getY(), 0);
}


TEST_F(EngineMovementTest, MovementTestSouth) {

    d1->setX(0); d1->setY(50);
    d2->setX(0); d2->setY(0);

    d1->setDirection(util::SOUTH);

    // no collision problems should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 0);
    EXPECT_EQ(d1->getY(), 25);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 0);
    EXPECT_EQ(d1->getY(), hb->getHeight());

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 0);
    EXPECT_EQ(d1->getY(), hb->getHeight());
}

TEST_F(EngineMovementTest, MovementTestWest) {

    d1->setX(50); d1->setY(0);
    d2->setX(0); d2->setY(0);

    d1->setDirection(util::WEST);

    // no collision problems should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), 25);
    EXPECT_EQ(d1->getY(), 0);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), hb->getWidth());
    EXPECT_EQ(d1->getY(), 0);

    // a collision problem should occur
    Clock::setActive(true);
    Bitz::enqueueMovementEvent(d1, 25);
    Bitz::enqueueEvent(getStopClockEvent());
    Clock::runClock();

    EXPECT_EQ(d1->getX(), hb->getWidth());
    EXPECT_EQ(d1->getY(), 0);
}