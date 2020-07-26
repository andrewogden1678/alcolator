#include "Beverage.h"

Beverage::Beverage(int pk, std::string name, double concentration)
                    : Model(pk), name_(name), concentration_(concentration) {};

std::vector<std::string> Beverage::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Name of beverage
    returnVec.push_back(Database::FormatStringSQL(this->name_))
    // Beverage concentration
    returnVec.push_back(std::to_string(this->concentration_));

    // Return the vector
    return returnVec;
}