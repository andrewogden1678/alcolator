#include "ActionLog.h"

ActionLog::ActionLog(int pk, int identity_id, std::string message, std::string created_on) 
                    : Model(pk), message_(message), created_on_(created_on) {
    // Map foreign key to object
    this->identity_ = Database::instance()->GetForeignKey(identity_id);
};

std::vector<std::string> ActionLog::Serialise() {
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Identity
    returnVec.push_back(std::to_string(this->identity_->pk_));
    // Message
    returnVec.push_back(Database::FormatStringSQL(this->message_))
    // Date created on
    returnVec.push_back(Database::FormatStringSQL(this->created_on_))

    // Return the vector
    return returnVec;
}