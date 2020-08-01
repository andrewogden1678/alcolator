// Imports & Namespaces
#pragma once
#include <string>
#include <vector>
#include <array>
#include "../Database.h"

///
/// Model Base Class
///
class Model {

    // Constructor/Destructor
    public:
        Model(int pk) : pk_(pk) {};
        virtual ~Model() {};

        // Get members in format that can be processed by SQL
        virtual std::vector<std::string> Serialise() = 0;

        // Get primary key
        int GetPK() {
            return this->pk_;
        }
        
    protected:
        // Primary key (shared across all models)
        int pk_;
};