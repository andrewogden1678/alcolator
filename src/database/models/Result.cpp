#include "Result.h"

// Assign table name and column array
std::string Result::tableName_ = "results";
std::array<std::string, 8> Result::columns_ = {"subject_id", "beverage_id", "target_bac", "target_bac_time", 
                                    "amount_grams", "amount_beverage", "actual_bac", "actual_bac_time"};

// Constructor (new object)
Result::Result(int pk, int subject_id, int beverage_id,
                    double target_bac, int target_bac_time, double amount_grams, 
                    double amount_beverage, double actual_bac, std::string actual_bac_time)
                    : Model(pk), subject_(Database::Instance()->GetForeignKey<Subject>(subject_id)),
                    beverage_(Database::Instance()->GetForeignKey<Beverage>(beverage_id)),
                    target_bac_(target_bac), target_bac_time_(target_bac_time), amount_grams_(amount_grams), 
                    amount_beverage_(amount_beverage), actual_bac_(actual_bac), actual_bac_time_(actual_bac_time) {};

// Constructor (SQL callback)
Result::Result(char** fields) : Model(std::stoi(fields[0])), 
                    subject_(Database::Instance()->GetForeignKey<Subject>(std::stoi(fields[1]))),
                    beverage_(Database::Instance()->GetForeignKey<Beverage>(std::stoi(fields[2]))),
                    target_bac_(atof(fields[3])), target_bac_time_(std::stoi(fields[4])),
                    amount_grams_(atof(fields[5])), amount_beverage_(atof(fields[6])),
                    actual_bac_(atof(fields[7])), actual_bac_time_(Database::ToStdString(fields[8])) {};

// Serialise object values into an SQL-friendly format
std::vector<std::string> Result::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Subject
    returnVec.push_back(std::to_string(this->subject_.GetPK()));
    // Beverage
    returnVec.push_back(std::to_string(this->beverage_.GetPK()));
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
    returnVec.push_back(Database::FormatStringSQL(&this->actual_bac_time_));

    // Return the vector
    return returnVec;
}