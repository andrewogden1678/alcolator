#include "Model.h"
#include "Identity.h"

///
/// Model: ActionLog
///
class ActionLog : Model {

    public: 

        // Object constructor
        ActionLog(int pk, int identity_id, std::string message, std::string created_on);
                    
        ~ActionLog();

        // Column list
        std::string columns[3] = {"identity_id", "message", "created_on"};

        // Override members to strings conversion
        virtual std::vector<std::string> ConvertMembersSQL() override;

        /// DB Members
        // Foreign key to an Identity (One<->One)
        Identity identity_;
        // Message
        std::string message_;
        // Date created
        std::string created_on_;      
};