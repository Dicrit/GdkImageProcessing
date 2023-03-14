cmake_minimum_required(VERSION 3.15)


project(GdkIamgeProcessing VERSION 1.0)






add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)



add_executable(gdkIamgeProcessing main.cpp)

# find_package(Gtk 4 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
# pkg_check_modules(GTK REQUIRED gtk4)

target_include_directories(gdkIamgeProcessing PRIVATE ${GTKMM_INCLUDE_DIRS})

target_link_libraries(gdkIamgeProcessing ${GTKMM_LIBRARIES})

# target_link_libraries(Playground PUBLIC ${EXTRA_LIBS} tutorial_compiler_flags)
