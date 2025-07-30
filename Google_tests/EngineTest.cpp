//
// Created by iwant on 7/30/2025.
//

#include <gtest/gtest.h>

#include "../src/app/model/Characters/Dummy.h"
#include "../src/include/Bitz.h"
#include "../src/include/Clock.h"

int modifyThis;

TEST(EngineTest, EnqueueOnlyOneEvent) {
    Dummy d = Dummy();
    modifyThis = 0;

    // events to enqueue
    Bitz::enqueueEvent(new Event(
      1,
      []() -> void {
          modifyThis = 1;
          Clock::setActive(false);
      },
      d
    ));
    Bitz::enqueueEvent(new Event(
      1,
      []() -> void {
          modifyThis = -999;
          Clock::setActive(false);
      },
      d
    ));

    // run the clock
    Clock::setActive(true);
    Clock::runClock();

    EXPECT_EQ(modifyThis, -999);
}