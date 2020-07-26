#include "Model.h"

///
/// Model: Beverage
///
class Beverage : Model {

    public: 
        // Object constructor
        Beverage(int pk, std::string name, double concentration);
                    
        ~Beverage();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;

        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        // Column list
        std::string columns[2] = {"name", "concentration"};

        /// DB Members
        // Beverage name
        std::string name_;
        // Alcohol concentration
        double concentration_;        

        private:
            // Table name
            std::string tableName_ = "beverages";
};