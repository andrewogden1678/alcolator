#pragma once
#include "Model.h"

///
/// Model: Beverage
///
class Beverage : public Model {

    public: 
        // Main object constructor
        Beverage(int pk, std::string name, double concentration);
                    
        // SQL Callback constructor
        Beverage(char** fields);

        // Default destructor
        ~Beverage() {};
        
        // OVERRIDES: Serialise() (Model.h)
        virtual std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 2> columns_;

        /// DB Members
        // Beverage name
        std::string name_;
        // Alcohol concentration
        double concentration_;        

        // Table name
        static std::string tableName_;
};