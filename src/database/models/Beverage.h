#include "Model.h"

///
/// Model: Beverage
///
class Beverage : Model {

    public: 

        // Object constructor
        Beverage(int pk, std::string first_name, std::string last_name_, AccessLevel access_level,
                    std::string username, std::string password)
                    : pk_(pk), first_name_(first_name), last_name_(last_name), access_level_(access_level),
                    username_(username_), password_(password) {};
                    
        ~Beverage();
        
        /// DB Members
        // Beverage name
        std::string name_;
        // Alcohol concentration
        double concentration_;        
}