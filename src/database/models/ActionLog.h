#include "Model.h"

///
/// Model: ActionLog
///
class ActionLog : Model {

    public: 

        // Object constructor
        ActionLog(int pk, int identity_id, std::string message, std::string created_on)
                    : Model(pk, "action_logs"), identity_id_(identity_id), 
                    message_(message), created_on_(created_on){};
                    
        ~ActionLog();

        // Instantiation list
        std::string members[3] = {"identity_id", "message", "created_on"};

        /// DB Members
        // Foreign key to an Identity (One<->One)
        int identity_id_;
        // Message
        std::string message_;
        // Date created
        std::string created_on_;      
};