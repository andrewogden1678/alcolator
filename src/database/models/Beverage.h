#include "Model.h"

///
/// Model: Beverage
///
class Beverage : Model {

    public: 

        // Object constructor
        Beverage(int pk, std::string name, double concentration)
                    : Model(pk, "beverages"), name_(name), concentration_(concentration) {};
                    
        ~Beverage();
        
        // Instantiation list
        std::string members[2] = {"name", "concentration"};

        /// DB Members
        // Beverage name
        std::string name_;
        // Alcohol concentration
        double concentration_;        
};