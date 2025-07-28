//
// Created by Kyler on 7/24/2025.
// Used to showcase db functions at work

#include "sqlite_test.h"
#include <iostream>
#include "sqlite3.h"

void SQLite_test() {
    sqlite3* db;
    char* errMsg = nullptr;

    // 1. Open database (it will be created if it doesn't exist)
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Opened database successfully." << std::endl;

    // 2. Create table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS players ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name TEXT NOT NULL,"
                                 "score INTEGER);";

    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (create): " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully." << std::endl;
    }

    // 3. Insert data
    const char* insertSQL = "INSERT INTO players (name, score) VALUES ('Alice', 100);";
    rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (insert): " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data inserted successfully." << std::endl;
    }

    // 4. Query data
    const char* selectSQL = "SELECT id, name, score FROM players;";

    auto callback = [](void* NotUsed, int argc, char** argv, char** azColName) -> int {
        for (int i = 0; i < argc; ++i) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        }
        std::cout << std::endl;
        return 0;
    };

    rc = sqlite3_exec(db, selectSQL, callback, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (select): " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // 5. Close database
    sqlite3_close(db);
}