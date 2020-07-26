#include "Result.h"

Result::Result(int pk, int subject_id, int beverage_id,
                    double target_bac, int target_bac_time, double amount_grams, 
                    double amount_beverage, double actual_bac, std::string actual_bac_time)
                    : Model(pk), subject_id_(subject_id), beverage_id_(beverage_id), target_bac_(target_bac),
                    target_bac_time_(target_bac_time), amount_grams_(amount_grams), amount_beverage_(amount_beverage),
                    actual_bac_(actual_bac), actual_bac_time_(actual_bac_time) {
    // Map foreign keys to object
    this->subject_ = Database::instance()->GetForeignKey(subject_id);
    this->beverage_ = Database::instance()->GetForeignKey(beverage_id);
};

std::vector<std::string> Result::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Subject
    returnVec.push_back(std::to_string(this->subject_->pk_));
    // Beverage
    returnVec.push_back(std::to_string(this->beverage_->pk_));
    // Target BAC
    returnVec.push_back(std::to_string(this->target_bac_));
    // Time reaching target BAC
    returnVec.push_back(std::to_string(this->target_bac_time_));
    // Amount of alcohol (grams)
    returnVec.push_back(std::to_string(this->amount_grams_));
    // Amount of alcohol (beverage unit)
    returnVec.push_back(std::to_string(this->amount_beverage_));
    // Actual recorded BAC
    returnVec.push_back(std::to_string(this->actual_bac_));
    // Time BAC was recorded at
    returnVec.push_back(Database::FormatStringSQL(this->actual_bac_time_));

    // Return the vector
    return returnVec;
}