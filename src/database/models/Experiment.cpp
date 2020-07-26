#include "Experiment.h"

Experiment(int pk, std::string name, bool is_concluded)
                    : Model(pk), name_(name), is_concluded_(is_concluded) {};

std::vector<std::string> Experiment::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Name of experiment
    returnVec.push_back(Database::FormatStringSQL(this->name_))
    // Is the experiment concluded?
    returnVec.push_back(std::to_string(this->is_concluded_));

    // Return the vector
    return returnVec;
}