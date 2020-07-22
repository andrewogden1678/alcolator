#include "Model.h"

///
/// Model: ActionLog
///
class ActionLog : Model {

    public: 

        // Object constructor
        ActionLog(int pk, int identity_id, std::string message, std::string created_on)
                    : pk_(pk), identity_id_(identity_id), message_(message), created_on_(created_on), tableName_("action_logs"){};
                    
        ~ActionLog();

        /// DB Members
        // Foreign key to an Identity (One<->One)
        int identity_id_;
        // Message
        std::string message_;
        // Date created
        std::string created_on_;      
}