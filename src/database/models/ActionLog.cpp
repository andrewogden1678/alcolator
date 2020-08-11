#include "ActionLog.h"

// Assign table name and column array
std::string ActionLog::tableName_ = "action_logs";
std::array<std::string, 3> ActionLog::columns_ {"identity_id", "message", "created_on"};

// Constructor (new object)
ActionLog::ActionLog(int pk, int identity_id, std::string message, std::string created_on) 
                    : Model(pk), identity_(Database::Instance()->GetForeignKey<Identity>(identity_id)),
                    message_(message), created_on_(created_on) {};

// Constructor (SQL callback)
ActionLog::ActionLog(char** fields) : Model(int32_t(fields[0])), 
                    identity_(Database::Instance()->GetForeignKey<Identity>(std::stoi(fields[1]))),
                    message_(Database::ToStdString(fields[2])), created_on_(Database::ToStdString(fields[3])) {};

// Serialise object values into an SQL-friendly format
std::vector<std::string> ActionLog::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Identity
    returnVec.push_back(std::to_string(this->identity_.GetPK()));
    // Message
    returnVec.push_back(Database::FormatStringSQL(&this->message_));
    // Date created on
    returnVec.push_back(Database::FormatStringSQL(&this->created_on_));

    // Return the vector
    return returnVec;
}