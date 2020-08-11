#pragma once
#include "Model.h"
#include "Experiment.h"
#include "Identity.h"

///
/// Model: Subject
///
class Subject : public Model {

    public: 
        // Object constructor
        Subject(int pk, std::string subject_code, int experimenter_id, int experiment_id,
                    int age, bool gender, double height, double weight, std::string created_on);

        // SQL Callback constructor
        Subject(char** fields);

        // Default constructor
        ~Subject() {};

        // OVERRIDES: Serialise() (Model.h)
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() {
            return tableName_;
        }

        // Column list
        static std::array<std::string, 8> columns_;

        /// DB Members
        // Specific code for subject
        std::string subject_code_;
        // Foreign key to an Identity (One<->One)
        Identity experimenter_;
         // Foreign key to an Experiment(One<->One)
        Experiment experiment_;
        // Subject age
        int age_;
        // Subject gender
        bool gender_;
        // Subject height
        double height_;
        // Subject weight
        double weight_;
        // Date created on
        std::string created_on_;       

        // Table name
        static std::string tableName_;
};