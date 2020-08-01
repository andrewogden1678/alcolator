#include "Experiment.h"

// Assign table name and column array
std::string Experiment::tableName_ = "experiments";
std::array<std::string, 2> Experiment::columns_ = {"name", "is_concluded"};

Experiment::Experiment(int pk, std::string name, bool is_concluded)
                    : Model(pk), name_(name), is_concluded_(is_concluded) {};

// SQL Callback
Experiment::Experiment(char** fields) : Model(std::stoi(fields[0])), name_(Database::ToStdString(fields[1])),
                    is_concluded_(std::stoi(fields[2])) {};

std::vector<std::string> Experiment::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Name of experiment
    returnVec.push_back(Database::FormatStringSQL(&this->name_));
    // Is the experiment concluded?
    returnVec.push_back(std::to_string(this->is_concluded_));

    // Return the vector
    return returnVec;
}