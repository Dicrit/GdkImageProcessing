cmake_minimum_required(VERSION 3.15)


project(GdkIamgeProcessingGUILib VERSION 1.0)

add_library(GdkIamgeProcessingGUILib STATIC 
Application.cpp 
MainWindow.cpp)

target_include_directories(GdkIamgeProcessingGUILib PRIVATE ${GTKMM_INCLUDE_DIRS})
