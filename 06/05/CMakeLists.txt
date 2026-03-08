cmake_minimum_required(VERSION 3.20)
project(PluginSystem)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.85 REQUIRED COMPONENTS filesystem dl)

add_library(plugin_one SHARED plugin_one.cpp)
add_library(plugin_two SHARED plugin_two.cpp)

add_executable(loader main.cpp)
target_link_libraries(loader PRIVATE Boost::filesystem Boost::dl)
if(UNIX)
    target_link_libraries(loader PRIVATE dl)
endif()