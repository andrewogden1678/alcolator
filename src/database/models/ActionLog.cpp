#include "ActionLog.h"

ActionLog::ActionLog(int pk, int identity_id, std::string message, std::string created_on) 
                    : Model(pk, "action_logs"), message_(message), created_on_(created_on) {


    // SELECT IDENTITY FOREIGN KEY HERE (something like below code)
    // Identity identity = Database::instance()->GetForeignKey(table_name, id)

};

std::vector<std::string> ActionLog::ConvertMembersSQL() {
    
    // Return vector
    std::vector<std::string> returnVec;

    /// Convert and add properties to vector
    // Identity
    std::string identity_id = this->identity_.pk_;
    returnVec.push_back(identity_id);
    // Message
    std::string message; 
    message += "'";
    message += this->message_;
    message += "'";
    returnVec.push_back(message);
    // Date created on
    std::string created_on;
    created_on += "'";
    created_on += this->created_on_;
    created_on += "'";
    returnVec.push_back(created_on);

    // Return the vector
    return returnVec;
}