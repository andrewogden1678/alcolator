project(Alcolator C CXX)

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/App.cmake)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(SOURCES "src/database/Database.h"
            "src/database/Database.cpp"
            "src/database/models/enums/AccessLevel.h"
            "src/database/models/Model.h"
            "src/database/models/ActionLog.h"
            "src/database/models/ActionLog.cpp"
            "src/database/models/Beverage.h"
            "src/database/models/Beverage.cpp"
            "src/database/models/Experiment.h"
            "src/database/models/Experiment.cpp"
            "src/database/models/Identity.h"
            "src/database/models/Identity.cpp"
            "src/database/models/Result.h"
            "src/database/models/Result.cpp"
            "src/database/models/Subject.h"
            "src/database/models/Subject.cpp"
            "src/Alcolator.h"
            "src/Alcolator.cpp"
            "src/view_controllers/ViewController.h"
            "src/view_controllers/ViewController.cpp"
            "src/view_controllers/LoginVC.h"
            "src/view_controllers/LoginVC.cpp"
            "src/view_controllers/AdminVC.h"
            "src/view_controllers/AdminVC.cpp"
            "src/view_controllers/MainVC.h"
            "src/view_controllers/MainVC.cpp"
            "src/database/models/enums/AccessLevel.h"
            "src/main.cpp")

find_package(SQLITE3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  add_app("${SOURCES}")
  target_link_libraries (Alcolator ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)