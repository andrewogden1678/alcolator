#include <sqlite3.h>
#include "models/Model.h"
#include "models/enums/SQLCommandType.h"
#include "models/enums/SQLCondition.h"
#include "models/enums/Model.h"
#include <string>
#include <vector>
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
        template <class T> int Insert(T* model) {
            // Get all object members
            std::vector<std::string> members = model->ConvertMembersSQL();

            // Error message to pass by ref
            char* errorMsg;

            // SQL insert statement template
            std::string stmt;
            stmt += "INSERT INTO ";
            stmt += model->GetTableName();
            stmt += " VALUES(";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<string>::iterator i = members.begin(); i != members.end(); i++) {
                // Add comma if not first item
                if (counter != 0) {
                    stmt += ",";
                }
                // Add the object member
                stmt += *members;

                // Increment counter
                counter++;
            }
            // Close brackets and end line
            stmt += ");";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);
            
            // Check success
            if (status != SQLITE_OK) {
                return 1; // Return error
                // do something with errMsg here
                sqlite3_free(errorMsg); // Free the space
            } else {
                return 0; // All ok
            }
        }

        // DELETE
        template <class T> int Delete(T* model) {
            // Get all object members
            std::vector<std::string> members = model->ConvertMembersSQL();

            // Error message to pass by ref
            char* errorMsg;

            // SQL delete statement template
            std::string stmt;
            stmt += "DELETE FROM ";
            stmt += model->GetTableName();
            stmt += " WHERE id = ";
            stmt += std::to_string(model->GetPK());
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                return 1; // Return error
                // todo: do something with errMsg here
                sqlite3_free(errorMsg); // Free the space
            } else {
                return 0; // All ok
            }
        }

        // UPDATE
        template <class T> int Update(T* model) {
            // Get all object members
            std::vector<std::string> members = model->ConvertMembersSQL();

            // Error message to pass by ref
            char* errorMsg;

            // SQL insert statement template
            std::string stmt;
            stmt += "UPDATE ";
            stmt += model->GetTableName();
            stmt += "SET ";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<string>::iterator i = members.begin(); i != members.end(); i++) {
                // Add comma if not first item
                if (counter != 0) {
                    stmt += ",";
                }
                // Add column name
                stmt += model->columns[counter];
                stmt += " = "
                // Add the object member
                stmt += *members;

                // Increment counter
                counter++;
            }
            // Condition & endline
            stmt += " WHERE id = ";
            stmt += std::to_string(model->GetPK());
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);
            
            // Check success
            if (status != SQLITE_OK) {
                return 1; // Return error
                // do something with errMsg here
                sqlite3_free(errorMsg); // Free the space
            } else {
                return 0; // All ok
            }
        }

    private:
        // Singleton instance
        static Database* instance_;

        // The SQLite database
        sqlite3* db_;

        // Private constructor, ensure that DB cannot be instantiated with new()
        Database();

        // SQL callback
        int Callback(void* data, int argc, char** argv, char** azColName);
};