#include "Model.h"

///
/// Model: Experiment
///
class Experiment : Model {

    public: 
        // Object constructor
        Experiment(int pk, std::string name, bool is_concluded);
                    
        ~Experiment();
        
        // Override members to strings conversion
        virtual std::vector<std::string> Serialise() override;
        
        // Get table name
        static std::string GetTableName() override {
            return this->tableName_;
        }

        // Column list
        std::string columns[2] = {"name", "is_concluded"};

        /// DB Members
        // Experiment name
        std::string name_;
        // Whether experiment is concluded or not
        bool is_concluded_;   

        private:
            // Table name
            std::string tableName_ = "experiments";
};