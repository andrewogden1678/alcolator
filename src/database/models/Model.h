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

    public:
        // Constructor
        Model(int pk) : pk_(pk) {};

        // Destructor
        virtual ~Model() {};

        // Get model members in an SQL friendly format
        virtual std::vector<std::string> Serialise() = 0;

        // Get primary key
        int GetPK() {
            return this->pk_;
        }
        
    protected:
        // Primary key (shared across all models)
        int pk_;
};