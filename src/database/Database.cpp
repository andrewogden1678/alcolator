#include "Database.h"
#define DB_PATH "Alcolator.db"

// Pointer to database singleton
Database* Database::instance_ = nullptr;

// Get the database instance
Database* Database::Instance() {
    // Ensure instance is only instantiated ONCE
    if (instance_ == nullptr) {
        instance_ = new Database();
        Database::Instance()->Connect();
    }
    // Return instance
    return(instance_);
}

// Connect to the database
int Database::Connect() {
    // Connection result
    int status = 0; 

    // Try to connect
    status = sqlite3_open(DB_PATH, &db_);

    // Check for any errors
    if (status) {
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
    sqlite3_close(db_);

    // Destroy the instance
    delete instance_;

    // We don't need this anymore
    db_ = nullptr;

    return 0;
}

// Format strings for SQL
std::string Database::FormatStringSQL(std::string* str) {
    // Add preceding and trailing quotations
    std::string temp;
    temp += "\"";
    temp += *str;
    temp += "\"";

    // Return
    return temp;
}

// Format char* to string
std::string Database::ToStdString(char* str) {
    // Define, append and return
    std::string temp;
    temp += str;
    return temp;
}