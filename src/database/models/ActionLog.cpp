#include "ActionLog.h"

// SQL query string serialisation implementation
std::string ActionLog::SerialiseSQL(SQLCommandType sqlCommand, SQLCondition cond = NULL, std::string comparison = NULL) {

    switch (sqlCommand) {
        case SQLCommandType::SELECT:

            break;
        case SQLCommandType::INSERT:

            break;
        case SQLCommandType::UPDATE:

            break;
        case SQLCommandType::DELETE:
    }
}