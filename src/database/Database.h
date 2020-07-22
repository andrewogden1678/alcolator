#include <sqlite3.h>
#include "models/Model.h"
#include "models/enums/SQLCommandType.h"
#include "models/enums/SQLCondition.h"

///
/// Database driver
///
class Database {

    public:
        // The database instance (grabs the singleton)
        static Database* Instance();

        // Connect
        int Connect();

        // Disconnect
        int Disconnect();

        // DB query execution template
        template <class T> void Execute(T* model, SQLCommandType sqlCommand, SQLCondition cond = NULL, std::string comparison = NULL) {
            model.SerialiseSQL(sqlCommand, cond, comparison);

            // DB execution here
        }
        

    private:
        // Singleton instance
        static Database* instance_;

        // The SQLite database
        sqlite3 db_;

        // Private constructor, ensure that DB cannot be instantiated with new()
        Database();
}