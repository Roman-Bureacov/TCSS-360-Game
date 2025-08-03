//
// Created by iwant on 8/2/2025.
//

#include "../../src/include/Hitbox.h"
#include "gtest/gtest.h"

TEST(HitboxTest, ContainsTest) {
    // hitbox at (0, 0)
    const Hitbox h = Hitbox(util::Point(), 10, 10);

    const bool doesContain = h.contains(util::Point(5, 5));
    const bool doesContainOnEdge = h.contains(util::Point(10, 10));
    const bool doesNotContain = h.contains(util::Point(11, 11));

    EXPECT_TRUE(doesContain);
    EXPECT_TRUE(doesContainOnEdge);
    EXPECT_FALSE(doesNotContain);
}