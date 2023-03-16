cmake_minimum_required(VERSION 3.15)


project(GdkIamgeProcessingGUILib VERSION 1.0)

add_library(GdkIamgeProcessingGUILib STATIC 
Application.cpp 
MainWindowController.cpp
UserDataProvider.cpp
)


configure_file(MainWindow.xml ${CMAKE_BINARY_DIR}/MainWindow.xml COPYONLY)


target_include_directories(GdkIamgeProcessingGUILib PRIVATE "${CMAKE_SOURCE_DIR}/core" ${GTKMM_INCLUDE_DIRS})
