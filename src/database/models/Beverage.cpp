#include "Beverage.h"

// Assign table name and column array
std::string Beverage::tableName_ = "beverages";
std::array<std::string, 2> Beverage::columns_ = {"name", "concentration"};

// Constructor (new object)
Beverage::Beverage(int pk, std::string name, double concentration)
                    : Model(pk), name_(name), concentration_(concentration) {};

// Constructor (SQL callback)
Beverage::Beverage(char** fields) : Model(std::stoi(fields[0])), name_(Database::ToStdString(fields[1])),
                    concentration_(atof(fields[2])) {};

// Serialise object values into an SQL-friendly format
std::vector<std::string> Beverage::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Name of beverage
    returnVec.push_back(Database::FormatStringSQL(&this->name_));
    // Beverage concentration
    returnVec.push_back(std::to_string(this->concentration_));

    // Return the vector
    return returnVec;
}