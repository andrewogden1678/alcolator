#pragma once
#include "Model.h"

///
/// Model: Experiment
///
class Experiment : public Model {

    public: 
        // Main object constructor
        Experiment(int pk, std::string name, bool is_concluded);
        
        // SQL Callback constructor
        Experiment(char** fields);

        ~Experiment() {};
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 2> columns_;

        /// DB Members
        // Experiment name
        std::string name_;
        // Whether experiment is concluded or not
        bool is_concluded_;   

        // Table name
        static std::string tableName_;
};