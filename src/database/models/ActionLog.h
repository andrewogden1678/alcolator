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
        virtual std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        /// DB Members
        // Foreign key to an Identity (One<->One)
        Identity identity_;
        // Message
        std::string message_;
        // Date created
        std::string created_on_;      

        private:
            // Table name
            std::string tableName_ = "action_logs";
};