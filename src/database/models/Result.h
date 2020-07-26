#include "Model.h"

///
/// Model: Result
///
class Result : Model {

    public: 
        // Object constructor
        Result(int pk, int subject_id, int beverage_id,
                    double target_bac, int target_bac_time, double amount_grams, 
                    double amount_beverage, double actual_bac, std::string actual_bac_time)
                    : Model(pk, "results"), subject_id_(subject_id), beverage_id_(beverage_id), target_bac_(target_bac),
                    target_bac_time_(target_bac_time), amount_grams_(amount_grams), amount_beverage_(amount_beverage),
                    actual_bac_(actual_bac), actual_bac_time_(actual_bac_time) {};
                    
        ~Result();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Column list
        std::string columns[8] = {"subject_id", "beverage_id", "target_bad", "target_bac_time", 
                                    "amount_grams", "amount_beverage", "actual_bac", "actual_bac_time"};

        /// DB Members
        // Foreign key to a Subject (One<->One)
        int subject_id_;
         // Foreign key to a Beverage (One<->One)
        int beverage_id_;
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
};