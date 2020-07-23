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
                    : pk_(pk), subject_id_(subject_id), beverage_id_(beverage_id), target_bac_(target_bac),
                    target_bac_time_(target_bac_time), amount_grams_(amount_grams), amount_beverage_(amount_beverage),
                    actual_bac_(actual_bac), actual_bac_time_(actual_bac_time_) {};
                    
        ~Result();
        
        /// DB Members
        // Foreign key to a Subject (One<->One)
        const int subject_id_;
         // Foreign key to a Beverage (One<->One)
        const int beverage_id_;
        // Target BAC
        const double target_bac_;
        // BAC Target time
        const int target_bac_time_;
        // Amount of alcohol (grams)
        const double amount_grams_;
        // Amount of alcohol (beverage unit)
        const double amount_beverage_;
        // Actual recorded BAC
        const double actual_bac_;
        // Time BAC was recorded
        const std::string actual_bac_time_;       
}