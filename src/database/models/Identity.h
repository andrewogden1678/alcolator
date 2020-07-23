#include "Model.h"
#include "enums/AccessLevel.h"

///
/// Model: Identity
///
class Identity : Model {

    public: 

        // Object constructor
        Identity(int pk, std::string first_name, std::string last_name, AccessLevel access_level,
                    std::string username, std::string password)
                    : Model(pk, "identities"), first_name_(first_name), last_name_(last_name), access_level_(access_level),
                    username_(username_), password_(password) {};
                    
        ~Identity();
        
        // Override members to strings conversion
        virtual std::vector<std::string> ConvertMembersSQL() override;

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
};