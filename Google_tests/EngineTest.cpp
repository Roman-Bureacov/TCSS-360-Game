//
// Created by iwant on 7/30/2025.
//

#include <gtest/gtest.h>

#include "../src/app/model/Characters/Dummy.h"
#include "../src/include/Bitz.h"
#include "../src/include/Clock.h"

int modifyThis;

/**
 * Tests if only one event is enqueued at a time.
 */
TEST(EngineTest, EnqueueOnlyOneEvent) {
    Dummy d = Dummy();
    modifyThis = 0;

    // events to enqueue
    Bitz::enqueueEvent(new Event(
      1,
      []() -> void {
          modifyThis += 1;
          Clock::setActive(false);
      },
      d
    ));
    Bitz::enqueueEvent(new Event(
      1,
      []() -> void {
          modifyThis += -999;
          Clock::setActive(false);
      },
      d
    ));

    // run the clock
    Clock::setActive(true);
    Clock::runClock();

    EXPECT_EQ(modifyThis, -999);
}

/**
 * Tests if the persistent events count for more than 1 tick.
 */
TEST(EngineTest, PersistentEvent) {
    modifyThis = 0;
    Bitz::enqueueEvent(new Event(
        3,
        []() -> void {
            modifyThis++;
            if (modifyThis == 3) {
                Clock::setActive(false);
            }
        },
        Dummy()
        )
    );
    Clock::setActive(true);
    Clock::runClock();

    EXPECT_EQ(modifyThis, 3);
}

/**
* Tests if the persistent events prevent from enqueueing additional events by the same character.
*/
TEST(EngineTest, PersistentQueueEventPrevention) {
    const Dummy d = Dummy();

    modifyThis = 0;
    Event* persistentEvent = new Event(
        2,
        []() -> void {
            modifyThis++;
            Clock::setActive(false);
        }, d);
    Event* singleEvent = new Event(
        1,
        []() -> void {
            modifyThis = -999;
            Clock::setActive(false);
        }, d);

    Bitz::enqueueEvent(persistentEvent);
    Clock::setActive(true);
    Clock::runClock();
    Bitz::enqueueEvent(singleEvent);
    Clock::setActive(true);
    Clock::runClock();

    EXPECT_EQ(modifyThis, 2);
}
