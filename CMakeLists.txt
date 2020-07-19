project(Alcolator C CXX)

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/App.cmake)

set(SOURCES "src/Alcolator.h"
            "src/Alcolator.cpp"
            "src/view_controllers/ViewController.h"
            "src/view_controllers/LoginVC.h"
            "src/view_controllers/LoginVC.cpp"
            "src/view_controllers/AdminVC.h"
            "src/view_controllers/AdminVC.cpp"
            "src/view_controllers/MainVC.h"
            "src/view_controllers/MainVC.cpp"
            "src/main.cpp")

add_app("${SOURCES}")