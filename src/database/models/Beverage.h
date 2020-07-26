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
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;

        // Column list
        std::string columns[2] = {"name", "concentration"};

        /// DB Members
        // Beverage name
        std::string name_;
        // Alcohol concentration
        double concentration_;        
};