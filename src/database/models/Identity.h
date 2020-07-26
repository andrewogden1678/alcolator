#include "Model.h"
#include "enums/AccessLevel.h"

///
/// Model: Identity
///
class Identity : Model {

    public: 
        // Object constructor
        Identity(int pk, std::string first_name, std::string last_name, AccessLevel access_level,
                    std::string username, std::string password);
                    
        ~Identity();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        // Column list
        std::string columns[5] = {"first_name", "last_name", "access_level", "username", "password"};

        /// DB Members
        // First name
        std::string first_name_;
        // Last name
        std::string last_name_;
        // Access level
        AccessLevel access_level_;
        // Username
        std::string username_;
        // Password
        std::string password_;

        private:
            // Table name
            std::string tableName_ = "identities";
};