#include "Database.h"

// Pointer to database singleton
Database* Database::instance_ = nullptr;

// Get the database instance
Database* Database::Instance() {
    // Ensure instance is only instantiated ONCE
    if (instance == nullptr) {
        instance = new Database();
    }
    // Return instance
    return(instance_);
}

// Connect to the database
int Database::Connect() {
    // Connection result
    int exit = 0; 

    // Try to connect
    exit = sqlite3_open("Alcolator.db", &db_);

    // Check for any errors
    if (exit) {
        // There was an error so return code 1
        return 1;
    } else {
        // Connection successful, return 1
        return 0;
    }
}

// Disconnect from the database
int Database::Disconnect() {
    // Close the database
    sqlite3_close(db_)

    // We don't need this anymore
    db_ = nullptr;
}