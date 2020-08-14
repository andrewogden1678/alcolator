#pragma once
#include "Model.h"
#include "Subject.h"
#include "Beverage.h"

///
/// Model: Result
///
class Result : public Model {

    public: 
        // Main object constructor
        Result(int pk, int subject_id, int beverage_id,
                    double target_bac, int target_bac_time, double amount_grams, 
                    double amount_beverage, double alcvol, double actual_bac, std::string actual_bac_time);

        // SQL Callback constructor
        Result(char** fields);

        // Default constructor
        ~Result() {};
        
        // OVERRIDES: Serialise() (Model.h)
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 9> columns_;

        /// DB Members
        // Foreign key to a Subject (One<->One)
        Subject subject_;
         // Foreign key to a Beverage (One<->One)
        Beverage beverage_;
        // Target BAC
        double target_bac_;
        // BAC Target time
        int target_bac_time_;
        // Amount of alcohol (grams)
        double amount_grams_;
        // Amount of alcohol (beverage unit)
        double amount_beverage_;
        // Alcohol volume
        double alcvol_;
        // Actual recorded BAC
        double actual_bac_;
        // Time BAC was recorded
        std::string actual_bac_time_;       

        // Table name
        static std::string tableName_;
};