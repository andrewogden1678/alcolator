#include "Subject.h"

// Assign table name and column array
std::string Subject::tableName_ = "subjects";
std::array<std::string, 8> Subject::columns_ = {"subject_code", "experimenter_id", "experiment_id", "age", 
                                    "gender", "height", "weight", "created_on"};

Subject::Subject(int pk, std::string subject_code, int experimenter_id, int experiment_id,
                    int age, bool gender, double height, double weight, std::string created_on)
                    : Model(pk), subject_code_(subject_code), 
                    experimenter_(Database::Instance()->GetForeignKey<Identity>(experimenter_id)), 
                    experiment_(Database::Instance()->GetForeignKey<Experiment>(experiment_id)),
                    age_(age), gender_(gender), height_(height), weight_(weight), created_on_(created_on) {};

// SQL Callback
Subject::Subject(char** fields) : Model(std::stoi(fields[0])), 
                    subject_code_(Database::ToStdString(fields[1])),
                    experimenter_(Database::Instance()->GetForeignKey<Identity>(std::stoi(fields[2]))),
                    experiment_(Database::Instance()->GetForeignKey<Experiment>(std::stoi(fields[3]))),
                    age_(std::stoi(fields[4])), gender_(std::stoi(fields[5])), height_(atof(fields[6])),
                    weight_(atof(fields[7])), created_on_(Database::ToStdString(fields[8])) {};

std::vector<std::string> Subject::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Subject code
    returnVec.push_back(Database::FormatStringSQL(&this->subject_code_));
    // Experimenter identity
    returnVec.push_back(std::to_string(this->experimenter_.GetPK()));
    // Experiment
    returnVec.push_back(std::to_string(this->experiment_.GetPK()));
    // Age
    returnVec.push_back(std::to_string(this->age_));
    // Gender
    returnVec.push_back(std::to_string(this->gender_));
    // Height
    returnVec.push_back(std::to_string(this->height_));
    // Weight
    returnVec.push_back(std::to_string(this->weight_));
    // Subject code
    returnVec.push_back(Database::FormatStringSQL(&this->created_on_));

    // Return the vector
    return returnVec;
}