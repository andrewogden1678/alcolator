#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
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
        
        // String formatter to account for quotes in string
        static std::string FormatStringSQL(std::string* str);

        // Get string from char array
        static std::string ToStdString(char* str);

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
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback<T>, &selected, &errMsg);

            // Check success
            if (status != SQLITE_OK) {                        
                throw errMsg; // Throw error             
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
            stmt += " WHERE ";
            stmt += "id";
            stmt += "=";
            stmt += std::to_string(id);
            stmt += ";";

            // Execute the query
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback<T>, &selected, &errMsg);

            // Check success
            if (status != SQLITE_OK) {                
                try {
                    throw errMsg; // Throw error         
                } catch(std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
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
            stmt += " WHERE ";
            stmt += column;
            stmt += " ";
            stmt += condition;
            stmt += " ";
            stmt += comparison;
            stmt += ";";

            // Execute the query
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), SelectCallback<T>, &selected, &errMsg);
            
            // Check success
            if (status != SQLITE_OK) {
                throw errMsg; // Throw error             
            } else {
                return selected; // All ok, return the records
            }
        }

        // Get Foreign key
        template <class T>
        T GetForeignKey(int id) {
            // Return the object
            return this->Select<T>(id);
        }

        // INSERT
        template <class T> 
        int Insert(T* model) {
            // Get all object members
            std::vector<std::string> members = model->Serialise();
            // Construct insert query
            std::string stmt;
            stmt += "INSERT INTO ";
            stmt += T::GetTableName();
            stmt += "(";
            try {
                // Add columns
                for (uint32_t i = 0; i < model->columns_.size(); i++) {
                    // Add comma if not first item
                    if (i != 0) {
                        stmt += ",";
                    }
                    
                    // Add the object member
                    stmt += model->columns_[i];
                }
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
            stmt += ") ";
            stmt += " VALUES(";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<std::string>::iterator i = members.begin(); i != members.end(); i++) {
                // Add comma if not first item
                if (counter != 0) {
                    stmt += ",";
                }
                // Add the object member
                stmt += *i;

                // Increment counter
                counter++;
            }
            // Close brackets and end line
            stmt += ");";
            
            // Execute the query
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);
            
            // Check success
            if (status != SQLITE_OK) {
                throw errMsg; // Throw error
                return 1;
            } else {
                return 0; // All ok
            }
        }

        // DELETE
        template <class T> 
        int Delete(int id) {

            // Construct delete query
            std::string stmt;
            stmt += "DELETE FROM ";
            stmt += T::GetTableName();
            stmt += " WHERE id = ";
            stmt += std::to_string(id);
            stmt += ";";

            // Execute the query
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);

            // Check success
            if (status != SQLITE_OK) {
                throw errMsg; // Throw error
            } else {
                return 0; // All ok
            }
        }

        // UPDATE
        template <class T> 
        int Update(T* model, std::string excluded = "none") {
            // Get all object members
            std::vector<std::string> members = model->Serialise();

            // Construct update query
            std::string stmt;
            stmt += "UPDATE ";
            stmt += T::GetTableName();
            stmt += " SET ";
            // Add items
            int counter = 0; // Counter for formatting
            for (std::vector<std::string>::iterator i = members.begin(); i != members.end(); i++) {
                // Skip excluded column (for identity)
                if (model->columns_[counter] == excluded) {
                    continue;
                }

                // Add comma if not first item
                if (counter != 0) {
                    stmt += ",";
                }
                // Add column name
                stmt += model->columns_[counter];
                stmt += " = ";
                // Add the object member
                stmt += *i;

                // Increment counter
                counter++;
            }
            // Condition & endline
            stmt += " WHERE id = ";
            stmt += std::to_string(model->GetPK());
            stmt += ";";

            // Execute the query
            char* errMsg = 0;
            int status = sqlite3_exec(this->db_, stmt.c_str(), NULL, 0, &errMsg);
            
            // Check success
            if (status != SQLITE_OK) {
                throw errMsg; // Throw error
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
        Database() { db_ = nullptr; };

        // SQL callback
        template<class T>
        static int SelectCallback(void* data, int fieldCount, char** fields, char** colNames) {
            // Cast data to vector
            std::vector<T>* selected = static_cast<std::vector<T>*>(data);

            try {
                // Deserialise SQL data into the model and fill the vector
                selected->emplace_back(fields);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl; // Oops, something went wrong
                return 1;
            }   
            // Return success code
            return 0;
        }
};