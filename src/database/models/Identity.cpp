#include "Identity.h"

Identity::Identity(int pk, std::string first_name, std::string last_name, AccessLevel access_level,
                    std::string username, std::string password)
                    : Model(pk), first_name_(first_name), last_name_(last_name), access_level_(access_level),
                    username_(username_), password_(password) {};

std::vector<std::string> Identity::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // First name
    returnVec.push_back(Database::FormatStringSQL(this->first_name_))
    // Last name
    returnVec.push_back(Database::FormatStringSQL(this->last_name_))
    // Access level
    returnVec.push_back(std::to_string(this->access_level_));
    // Username
    returnVec.push_back(Database::FormatStringSQL(this->username_))
    // Password
    returnVec.push_back(Database::FormatStringSQL(this->password_))

    // Return the vector
    return returnVec;
}