//
// Created by iwant on 8/4/2025.
//

#include "../src/app/model/Characters/Dummy.h"
#include "gtest/gtest.h"

/**
 * Specifically tests if the hitbox is placed in the right spot.
 * Character hitbox: 20x20 at (0,0)
 * Weapon hitbox: 10x10
 */
class CharacterHitboxTest : public ::testing::Test {
protected:
    inline static auto d = Dummy();
    inline static Hitbox dummyHitbox = Hitbox(20, 20);

    inline static Hitbox weaponHitbox = Hitbox(10, 10);
    inline static int hitboxWidth = 10;
    inline static int hitboxHeight = 10;
    inline static Weapon w = Weapon(1, 10, std::move(weaponHitbox));

    inline static util::Point pActual;

    static void SetUpTestSuite() {
        d.setHitbox(dummyHitbox);
        d.giveWeapon(&w);
        d.setDirection(util::NORTH);
    }
};

TEST_F(CharacterHitboxTest, AttackHitboxNorth) {

    d.setDirection(util::NORTH);
    pActual = d.getAttackHitbox().getOrigin();

    EXPECT_EQ(
        CharacterHitboxTest::pActual.x,
        20 - (20 + 10)/2
    );
    EXPECT_EQ(
        CharacterHitboxTest::pActual.y,
        20
    );

}

TEST_F(CharacterHitboxTest, AttackHitboxEast) {

    d.setDirection(util::EAST);
    pActual = d.getAttackHitbox().getOrigin();

    EXPECT_EQ(
        CharacterHitboxTest::pActual.x,
        20
    );
    EXPECT_EQ(
        CharacterHitboxTest::pActual.y,
        20 - (20 + 10)/2
    );

}

TEST_F(CharacterHitboxTest, AttackHitboxSouth) {

    d.setDirection(util::SOUTH);
    pActual = d.getAttackHitbox().getOrigin();

    EXPECT_EQ(
        CharacterHitboxTest::pActual.x,
        20 - (20 + 10)/2
    );
    EXPECT_EQ(
        CharacterHitboxTest::pActual.y,
        -20
    );

}

TEST_F(CharacterHitboxTest, AttackHitboxWest) {

    d.setDirection(util::WEST);
    pActual = d.getAttackHitbox().getOrigin();

    EXPECT_EQ(
        CharacterHitboxTest::pActual.x,
        -20
    );
    EXPECT_EQ(
        CharacterHitboxTest::pActual.y,
        20 - (20 + 10)/2
    );

}