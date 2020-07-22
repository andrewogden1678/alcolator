#include "Model.h"

///
/// Model: Experiment
///
class Experiment : Model {

    public: 

        // Object constructor
        Experiment(int pk, std::string name, bool is_concluded)
                    : pk_(pk), name_(name), is_concluded_(is_concluded) {};
                    
        ~Experiment();
        
        /// DB Members
        // Experiment name
        std::string name_;
        // Whether experiment is concluded or not
        bool is_concluded_;   
}