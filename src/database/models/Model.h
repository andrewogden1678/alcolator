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
        Model();
        virtual ~Model();

    protected:
        // Serialise SQL into 
        std::string SerialiseSQL(SQLCommandType sqlCommand, SQLCondition cond = NULL, std::string comparison = NULL);

        // Table name
        std::string tableName_;

        // Primary key (shared across all models)
        int pk_;
}