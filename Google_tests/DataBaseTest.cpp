//
// Created by codyh on 8/21/2025.
//
#include "gtest/gtest.h"
#include <filesystem>
#include <memory>
#include "../src/include/DatabaseManager.h"
#include "../src/include/AbstractCharacter.h"

// ---- Minimal stubs for Room, AbstractCharacter, Weapon ----





TEST(DatabaseManagerTest, CanOpenDatabase) {
    namespace fs = std::filesystem;
    const std::string tempDbPath = "test_temp.db";

    // Ensure a clean slate
    if (fs::exists(tempDbPath)) {
        fs::remove(tempDbPath);
    }

    // Should not throw when creating/opening
    EXPECT_NO_THROW({
        DatabaseManager db(tempDbPath);
    });

    // File should now exist
    EXPECT_TRUE(fs::exists(tempDbPath));

    // Optional: check file size > 0 to ensure SQLite header is written
    EXPECT_GT(fs::file_size(tempDbPath), 0u);

    // Cleanup
    fs::remove(tempDbPath);
}

TEST(DatabaseManagerTest, InsertAndLoadRoom) {
    const std::string tempDbPath = "test_temp.db";

    DatabaseManager db(tempDbPath);

    auto testRoom = std::make_shared<Room>();
    testRoom->setRoomID(1);
    db.insertRoom(*testRoom);

    auto loadedRoom = db.loadRoom(1);
    ASSERT_NE(loadedRoom, nullptr);
    EXPECT_EQ(loadedRoom->getRoomID(), 1);
}



TEST(DatabaseManagerTest, LoadNonexistentRoomThrowsRunTime) {
    const std::string tempDbPath = "test_temp.db";

    DatabaseManager db(tempDbPath);
    EXPECT_THROW({
        db.loadRoom(999);}, std::runtime_error);
}
