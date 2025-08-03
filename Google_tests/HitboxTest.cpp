//
// Created by iwant on 8/2/2025.
//

#include "../src/include/Hitbox.h"
#include "gtest/gtest.h"

Hitbox basicHitbox();

/**
 * Tests if the basic hitbox can correctly discern if it contains points.
 */
TEST(HitboxTest, ContainsTest) {
    // hitbox at (0, 0)
    const Hitbox h = basicHitbox();

    const bool doesContain = h.contains(util::Point(5, 5));
    const bool doesContainOnEdge = h.contains(util::Point(10, 10));
    const bool doesNotContain1 = h.contains(util::Point(11, 11));
    const bool doesNotContain2 = h.contains(util::Point(10, 11));
    const bool doesNotContain3 = h.contains(util::Point(0, -1));
    const bool doesNotContain4 = h.contains(util::Point(-1, 0));
    const bool doesNotContain5 = h.contains(util::Point(-1, -1));

    EXPECT_TRUE(doesContain);
    EXPECT_TRUE(doesContainOnEdge);
    EXPECT_FALSE(doesNotContain1);
    EXPECT_FALSE(doesNotContain2);
    EXPECT_FALSE(doesNotContain3);
    EXPECT_FALSE(doesNotContain4);
    EXPECT_FALSE(doesNotContain5);
}

TEST(HitboxTest, IntersectTest) {
    const Hitbox h = basicHitbox();
    const Hitbox topLeft = Hitbox(util::Point(-5, 5), 10, 10);
    const Hitbox topRight = Hitbox(util::Point(5, 5), 10, 10);
    const Hitbox botLeft = Hitbox(util::Point(-5, -5), 10, 10);
    const Hitbox botRight = Hitbox(util::Point(5, -5), 10, 10);
    const Hitbox edgeIntersect = Hitbox(util::Point(10, 10), 10, 10);
    const Hitbox notIntersect = Hitbox(util::Point(11, 11), 10, 10);

    EXPECT_TRUE(h.intersects(topLeft));
    EXPECT_TRUE(h.intersects(topRight));
    EXPECT_TRUE(h.intersects(botLeft));
    EXPECT_TRUE(h.intersects(botRight));
    EXPECT_TRUE(h.intersects(edgeIntersect));
    EXPECT_FALSE(h.intersects(notIntersect));
}

/**
 * Creates a generic hitbox for testing.
 * @return a hitbox centered at (0,0), a width of 10, and a height of 10
 */
Hitbox basicHitbox() {
    return Hitbox(util::Point(), 10, 10);
}