#pragma once
#include "Model.h"
#include "enums/AccessLevel.h"

///
/// Model: Identity
///
class Identity : public Model {

    public: 
        // Main object constructor
        Identity(int pk, std::string first_name, std::string last_name, AccessLevel access_level,
                    std::string username, std::string password);
                    
        // SQL Callback constructor
        Identity(char** fields);

        // Default destructor
        ~Identity() {};
        
        // OVERRIDES: Serialise() (Model.h)
        std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 5> columns_;

        /// DB Members
        // First name
        std::string first_name_;
        // Last name
        std::string last_name_;
        // Access level
        AccessLevel access_level_;
        // Username
        std::string username_;
        // Password
        std::string password_;

        // Table name
        static std::string tableName_;
};