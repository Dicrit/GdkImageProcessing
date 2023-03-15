cmake_minimum_required(VERSION 3.15)


project(GdkIamgeProcessing VERSION 1.0)

add_executable(gdkIamgeProcessing main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package(ImageMagick COMPONENTS Magick++)

add_subdirectory(core)
add_subdirectory(GUI)



target_include_directories(gdkIamgeProcessing PRIVATE 
"${CMAKE_CURRENT_SOURCE_DIR}/core" 
"${CMAKE_CURRENT_SOURCE_DIR}/GUI" 
${GTKMM_INCLUDE_DIRS} 
${ImageMagick_INCLUDE_DIRS})

target_link_libraries(gdkIamgeProcessing 
GdkIamgeProcessingCoreLib
GdkIamgeProcessingGUILib
${GTKMM_LIBRARIES}
 ${ImageMagick_LIBRARIES})
