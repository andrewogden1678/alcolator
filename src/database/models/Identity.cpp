#include "Identity.h"

// Assign table name and column array
std::string Identity::tableName_ = "identities";
std::array<std::string, 5> Identity::columns_ = {"first_name", "last_name", "access_level", "username", "password"};

Identity::Identity(int pk, std::string first_name, std::string last_name, AccessLevel access_level,
                    std::string username, std::string password)
                    : Model(pk), first_name_(first_name), last_name_(last_name), access_level_(access_level),
                    username_(username), password_(password) {};

// SQL Callback
Identity::Identity(char** fields) : Model(std::stoi(fields[0])), first_name_(Database::ToStdString(fields[1])), 
                                    last_name_(Database::ToStdString(fields[2])), access_level_(static_cast<AccessLevel>(std::stoi(fields[3]))),
                                    username_(Database::ToStdString(fields[4])), password_(Database::ToStdString(fields[5])) {};

std::vector<std::string> Identity::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // First name
    returnVec.push_back(Database::FormatStringSQL(&this->first_name_));
    // Last name
    returnVec.push_back(Database::FormatStringSQL(&this->last_name_));
    // Access level
    returnVec.push_back(std::to_string(static_cast<int>(this->access_level_)));
    // Username
    returnVec.push_back(Database::FormatStringSQL(&this->username_));
    // Password
    returnVec.push_back(Database::FormatStringSQL(&this->password_));

    // Return the vector
    return returnVec;
}