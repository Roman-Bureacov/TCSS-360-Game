//
// Created by riley on 8/18/25.
//

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "../src/include/Dungeon.h"
#include "../src/include/NPC.h"
#include "../src/include/Player.h"
#include "../src/include/Clock.h"


//These tests aren't super helpful since, if we're tweaking stats for balance they will fail


TEST(PLAYERTEST, EastWallColision) {
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    std::cout << allNPCs.size() << std::endl;

    auto player = Player::playerInstance();
    allNPCs[0]->setIsActive(false);


    //This will set the player exactly right outside the walls hitbox
    player->setX(((Room::ROOMSIZE - 1) * Room::TILESIZE) - player->getHitBoxSize());


    int testAmount = 10;

    for (int i = 0; i < testAmount;i++) {
        player->userInput(SDL_SCANCODE_D);
    }



    Clock::StopClockForTesting( testAmount);
    Clock::runClock();



    ASSERT_TRUE( player->getX() < Room::ROOMSIZE * Room::TILESIZE);


}


TEST(PLAYERTEST,WestWallColision) {
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    std::cout << allNPCs.size() << std::endl;

    auto player = Player::playerInstance();
    allNPCs[0]->setIsActive(false);


    //This will set the player exactly right outside the walls hitbox
    player->setX(player->getHitBoxSize());


    player->userInput(SDL_SCANCODE_A);

    int testAmount = 10;

    for (int i = 0; i < testAmount;i++) {
        player->userInput(SDL_SCANCODE_D);
    }

    Clock::StopClockForTesting( testAmount);
    Clock::runClock();

    ASSERT_TRUE(player->getX() > 0);
}


TEST(PLAYERTEST,northWallColision) {
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    auto player = Player::playerInstance();
    allNPCs[0]->setIsActive(false);


    //This will set the player exactly right outside the walls hitbox
    player->setY((Room::ROOMSIZE * Room::TILESIZE) - player->getHitBoxSize());



    int testAmount = 10;

    for (int i = 0; i < testAmount;i++) {
        player->userInput(SDL_SCANCODE_D);
    }



    Clock::StopClockForTesting( testAmount);
    Clock::runClock();


    ASSERT_TRUE(player->getY() < Room::ROOMSIZE *Room::TILESIZE);

}

TEST(PLAYERTEST, SouthWallColision) {
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    auto player = Player::playerInstance();
    allNPCs[0]->setIsActive(false);


    //This will set the player exactly right outside the walls hitbox
    player->setY(player->getHitBoxSize());

    int testAmount = 10;

    for (int i = 0; i < testAmount;i++) {
        player->userInput(SDL_SCANCODE_D);
    }



    Clock::StopClockForTesting( testAmount);
    Clock::runClock();


    ASSERT_TRUE(player->getY() > 0);

}

TEST(PLAYERTEST, AttackNPCTEST) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    auto player = Player::playerInstance();



    int statingHealth = allNPCs[0]->getHealth();


    allNPCs[0]->setX(player->getX() + player->getHitBoxSize());
    allNPCs[0]->setY(player->getY());

    player->setDirection(util::EAST);
    player->userInput(SDL_SCANCODE_SPACE);
    player->userInput(SDL_SCANCODE_SPACE);
    player->userInput(SDL_SCANCODE_SPACE);

    Clock::StopClockForTesting( 10);
    Clock::runClock();

    std::cout << "This is the hitBOx of an npc: " << allNPCs[0]->getHitbox().getHeight() << " " << allNPCs[0]->getHitbox().getWidth() << std::endl;


    ASSERT_NE(allNPCs[0]->getHealth(), statingHealth);


}

TEST(PLAYERTEST, changeClass) {
    auto player = Player::playerInstance();

    player->setClass(playerTypes::Rogue);
    ASSERT_EQ(player->getName(),PlayerClasses::MYNAMEROGUE);
    player->setClass(playerTypes::Knight);
    ASSERT_EQ(player->getName(),PlayerClasses::MYNAMEKNIGHT);
    player->setClass(playerTypes::Mage);
    ASSERT_EQ(player->getName(),PlayerClasses::MYNAMEMAGE);
    player->setClass(playerTypes::Archer);
    ASSERT_EQ(player->getName(),PlayerClasses::MYNAMEARCHER);


}

TEST(PLAYERTEST,potionTest) {


    auto player = Player::playerInstance();
    //Just so the player can be healed
    player->setHealth(1);
    player->setPotionAmount(0);

    //Player should start with no potions
    ASSERT_EQ(player->getPotionAmount(), 0);

    player->givePotion();
    ASSERT_EQ(player->myPotionAmount, 1);

    int currentPlayerHealth = player->getHealth();

    player->usePotion();

    ASSERT_EQ(player->getHealth(), currentPlayerHealth + Player::MYPOTIONSTRENGTH);

    ASSERT_EQ(player->getPotionAmount(), 0);


}

