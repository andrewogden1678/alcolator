#include "Model.h"
#include "Subject.h"
#include "Beverage.h"

///
/// Model: Result
///
class Result : Model {

    public: 
        // Object constructor
        Result(int pk, int subject_id, int beverage_id,
                    double target_bac, int target_bac_time, double amount_grams, 
                    double amount_beverage, double actual_bac, std::string actual_bac_time);
                    
        ~Result();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        // Column list
        std::string columns[8] = {"subject_id", "beverage_id", "target_bad", "target_bac_time", 
                                    "amount_grams", "amount_beverage", "actual_bac", "actual_bac_time"};

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
        // Actual recorded BAC
        double actual_bac_;
        // Time BAC was recorded
        std::string actual_bac_time_;       

        private:
            // Table name
            std::string tableName_ = "results";
};