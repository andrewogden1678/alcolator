// Imports & Namespaces
#include "enums/SQLCommandType.h"
#include "enums/SQLCondition.h"

using namespace std;

///
/// Model Base Class
///
class Model {

    // Constructor/Destructor
    public:
        Model(int pk, std::string tableName) : pk_(pk), tableName_(tableName) {};
        virtual ~Model();

    protected:
        /*
        std::string SerialiseSQL(SQLCommandType sqlCommand, SQLCondition cond = SQLCondition::ENULL, 
        std::string comparison = NULL) override;*/

        // Table name
        std::string tableName_;

        // Primary key (shared across all models)
        int pk_;
};