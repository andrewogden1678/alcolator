// Imports & Namespaces
#include "enums/SQLCommandType.h"
#include "enums/SQLCondition.h"
#include <string>
#include <vector>

using namespace std;

///
/// Model Base Class
///
class Model {

    // Constructor/Destructor
    public:
        Model(int pk, std::string tableName) : pk_(pk), tableName_(tableName) {};
        virtual ~Model();

        // Get members in format that can be processed by SQL
        virtual std::vector<std::string> ConvertMembersSQL();
        
        // Get tablename
        std::string GetTableName() {
            return this->tableName_;
        }

        // Get primary key
        int GetPK() {
            return this->pk_;
        }
    protected:
        /*
        std::string SerialiseSQL(SQLCommandType sqlCommand, SQLCondition cond = SQLCondition::ENULL, 
        std::string comparison = NULL) override;*/

        // Table name
        std::string tableName_;

        // Primary key (shared across all models)
        int pk_;
};