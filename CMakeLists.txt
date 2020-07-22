project(Alcolator C CXX)

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/App.cmake)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(SOURCES "src/Alcolator.h"
            "src/Alcolator.cpp"
            "src/view_controllers/ViewController.h"
            "src/view_controllers/ViewController.cpp"
            "src/view_controllers/LoginVC.h"
            "src/view_controllers/LoginVC.cpp"
            "src/view_controllers/AdminVC.h"
            "src/view_controllers/AdminVC.cpp"
            "src/view_controllers/MainVC.h"
            "src/view_controllers/MainVC.cpp"
            "src/main.cpp"
            "src/helpers/DatabaseHelper.h")

add_app("${SOURCES}")

find_package(SQLITE3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  target_link_libraries (Alcolator ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)