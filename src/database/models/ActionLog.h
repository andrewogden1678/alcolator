#pragma once
#include "Model.h"
#include "Identity.h"

///
/// Model: ActionLog
///
class ActionLog : public Model {

    public: 
        // Main object constructor
        ActionLog(int pk, int identity_id, std::string message, std::string created_on);

        // SQL Callback constructor
        ActionLog(char** fields);
                    
        ~ActionLog() {};

        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 3> columns_;

        /// DB Members
        // Foreign key to an Identity (One<->One)
        Identity identity_;
        // Message
        std::string message_;
        // Date created
        std::string created_on_;      

        // Table name
        static std::string tableName_;
};