#include <sqlite3.h>
#include "models/Model.h"
#include "models/enums/SQLCommandType.h"
#include "models/enums/SQLCondition.h"
#include "models/enums/Model.h"

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

        /// DB Query Execution
        // SELECT
        template <class T> void Select(Model model, SQLCommandType sqlCommand, SQLCondition cond = NULL, std::string comparison = NULL) {
            

        }

        // INSERT
        template <class T> void Insert(T* model) {
            

        }

        // UPDATE
        template <class T> void Update(T* model) {
            

        }

        // DELETE
        template <class T> void Delete(T* model) {
            

        }
        

    private:
        // Singleton instance
        static Database* instance_;

        // The SQLite database
        sqlite3* db_;

        // Private constructor, ensure that DB cannot be instantiated with new()
        Database();
};