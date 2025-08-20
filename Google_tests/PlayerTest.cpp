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


TEST(PLAYERTEST,movementEastTest) {
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


    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_D;

    //I'm too tired to write a getter.
    int finalX = player->getX() + 75;
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

}

TEST (PLAYERTEST,movementWestTest) {
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


    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_A;

    //I'm too tired to write a getter.
    int finalX = player->getX() - 75;
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());
}

TEST(PLAYERTEST, movementNorthTest) {
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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_W;

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY() + 75;


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalY, player->getY());
    ASSERT_EQ(finalX, player->getX());


}
TEST(PLAYERTEST, movementSouthTest) {
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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_S;

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY() - 75;


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

}

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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_D;
    player->setX(1500 - 10);

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_A;
    player->setX(0);

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

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


    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_W;
    player->setY(1500 - 10);

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_S;
    player->setY(0);

    //I'm too tired to write a getter.
    int finalX = player->getX();
    int finalY = player->getY();


    player->userInput(event);

    Clock::StopClockForTesting( 1);
    Clock::runClock();

    ASSERT_EQ(finalX, player->getX());
    ASSERT_EQ(finalY, player->getY());

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

    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_SPACE;

    allNPCs[0]->setX(player->getX() + 10);
    allNPCs[0]->setY(player->getY());

    player->setDirection(util::WEST);
    player->userInput(event);
    player->userInput(event);
    player->userInput(event);

    Clock::StopClockForTesting( 10);
    Clock::runClock();

    ASSERT_NE(allNPCs[0]->getHealth(), statingHealth);


}

