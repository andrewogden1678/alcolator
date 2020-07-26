#include "Model.h"

///
/// Model: Subject
///
class Subject : Model {

    public: 
        // Object constructor
        Subject(int pk, std::string subject_code, int experimenter_id, int experiment_id,
                    int age, bool gender, double height, double weight, std::string created_on)
                    : Model(pk, "subjects"), subject_code_(subject_code), experimenter_id_(experimenter_id), experiment_id_(experiment_id),
                    age_(age), gender_(gender), height_(height), weight_(weight), created_on_(created_on) {};

        ~Subject();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Column list
        std::string columns[8] = {"subject_code", "experimenter_id", "experiment_id", "age", 
                                    "gender", "height", "weight", "created_on"};

        /// DB Members
        // Specific code for subject
        std::string subject_code_;
        // Foreign key to an Identity (One<->One)
        int experimenter_id_;
         // Foreign key to an Experiment(One<->One)
        int experiment_id_;
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
};