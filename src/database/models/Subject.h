#include "Model.h"
#include "Experiment.h"
#include "Identity.h"

///
/// Model: Subject
///
class Subject : Model {

    public: 
        // Object constructor
        Subject(int pk, std::string subject_code, int experimenter_id, int experiment_id,
                    int age, bool gender, double height, double weight, std::string created_on);

        ~Subject();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        // Column list
        std::string columns[8] = {"subject_code", "experimenter_id", "experiment_id", "age", 
                                    "gender", "height", "weight", "created_on"};

        /// DB Members
        // Specific code for subject
        std::string subject_code_;
        // Foreign key to an Identity (One<->One)
        Experimenter experimenter_;
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

        private:
            // Table name
            std::string tableName_ = "subjects";
};