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
        // SELECT (ALL)
        template <class T> 
        std::vector<T> Select() {
            // Vector of T class
            std::vector<T> selected;

            // Construct select query
            std::string stmt;
            stmt += "SELECT * FROM ";
            stmt += T::GetTableName();
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback, &selected, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return {}; // Return empty vector                
            } else {
                return selected; // All ok, return the records
            }
        }

        // SELECT (ONE)
        template <class T> 
        T Select(int id) {
            // Vector of T class
            std::vector<T> selected;

            // Construct select query
            std::string stmt;
            stmt += "SELECT * FROM ";
            stmt += T::GetTableName();
            stmt += "WHERE ";
            stmt += "id";
            stmt += "=";
            stmt += to_string(id);
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback, &selected, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return {}; // Return empty vector                
            } else {
                return selected.at(0); // All ok, return the record (will always be at 0 position)
            }
        }

        // SELECT (CONDITIONAL)
        template <class T> 
        std::vector<T> Select(std::string column, std::string condition, std::string comparison) {
            // Vector of T class
            std::vector<T> selected;

            // Construct select query
            std::string stmt;
            stmt += "SELECT * FROM ";
            stmt += T::GetTableName();
            stmt += "WHERE ";
            stmt += column;
            stmt += condition;
            stmt += comparison;
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback, &selected, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return {}; // Return empty vector                
            } else {
                return selected; // All ok, return the records
            }
        }

        // Get Foreign key
        template <class T>
        T GetForeignKey(int id) {
            // Return the object
            return this->Select(id);
        }

        // INSERT
        template <class T> 
        int Insert(T* model) {
            // Get all object members
            std::vector<std::string> members = model->Serialise();

            // Error message to pass by ref
            char* errorMsg;

            // Construct insert query
            std::string stmt;
            stmt += "INSERT INTO ";
            stmt += model::GetTableName();
            stmt += " VALUES(";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<std::string>::iterator i = members.begin(); i != members.end(); i++) {
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
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return 1; // Return error code
            } else {
                return 0; // All ok
            }
        }

        // DELETE
        template <class T> 
        int Delete(T* model) {
            // Get all object members
            std::vector<std::string> members = model->Serialise();

            // Error message to pass by ref
            char* errorMsg;

            // Construct delete query
            std::string stmt;
            stmt += "DELETE FROM ";
            stmt += model::GetTableName();
            stmt += " WHERE id = ";
            stmt += std::to_string(model->GetPK());
            stmt += ";";

            // Execute the query
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return 1; // Return  error code
            } else {
                return 0; // All ok
            }
        }

        // UPDATE
        template <class T> 
        int Update(T* model) {
            // Get all object members
            std::vector<std::string> members = model->Serialise();

            // Error message to pass by ref
            char* errorMsg;

            // Construct update query
            std::string stmt;
            stmt += "UPDATE ";
            stmt += model::GetTableName();
            stmt += "SET ";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<std::string>::iterator i = members.begin(); i != members.end(); i++) {
                // Add comma if not first item
                if (counter != 0) {
                    stmt += ",";
                }
                // Add column name
                stmt += model->columns[counter];
                stmt += " = ";
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
                // do something with errMsg here
                sqlite3_free(errMsg); // Free the space
                return 1; // Return error code
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
        template<class T>
        static int SelectCallback(void* data, int fieldCount, char** fields, char** colNames) {
            // Cast data to vector
            std::vector<T>* selected = static_cast<std::vector<T>*>(data);

            try {
                // Deserialise SQL data into the model and fill the vector
                selected->emplace_back(fields, fields + fieldCount);
                // Return success code
                return 0;
            } catch (...) {
                return 1; // Oops, something went wrong
            }   
        }
};