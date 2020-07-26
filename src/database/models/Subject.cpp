#include "Subject.h"

Subject::Subject(int pk, std::string subject_code, int experimenter_id, int experiment_id,
                    int age, bool gender, double height, double weight, std::string created_on)
                    : Model(pk), subject_code_(subject_code), experimenter_id_(experimenter_id), experiment_id_(experiment_id),
                    age_(age), gender_(gender), height_(height), weight_(weight), created_on_(created_on) {
    // Map foreign keys to object
    this->experimenter_ = Database::instance()->GetForeignKey(experimenter_id);
    this->experiment_ = Database::instance()->GetForeignKey(experiment_id);
};

std::vector<std::string> Subject::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Subject code
    returnVec.push_back(Database::FormatStringSQL(this->subject_code_));
    // Experimenter identity
    returnVec.push_back(std::to_string(this->experimenter_->pk_));
    // Experiment
    returnVec.push_back(std::to_string(this->experiment_->pk_));
    // Age
    returnVec.push_back(std::to_string(this->age_));
    // Gender
    returnVec.push_back(std::to_string(this->gender_));
    // Height
    returnVec.push_back(std::to_string(this->height_));
    // Weight
    returnVec.push_back(std::to_string(this->weight_));
    // Subject code
    returnVec.push_back(Database::FormatStringSQL(this->created_on_));

    // Return the vector
    return returnVec;
}