#include "Model.h"
#include "enums/AccessLevel.h"

///
/// Model: Identity
///
class Identity : Model {

    public: 

        // Object constructor
        Identity(int pk, std::string first_name, std::string last_name_, AccessLevel access_level,
                    std::string username, std::string password)
                    : pk_(pk), first_name_(first_name), last_name_(last_name), access_level_(access_level),
                    username_(username_), password_(password) {};
                    
        ~Identity();

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
}