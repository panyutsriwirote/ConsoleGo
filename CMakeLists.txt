cmake_minimum_required(VERSION 3.23.1)
project(Go)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include_directories(./include)
if (WIN32)
    add_executable(go main.c board.c windows_display.c rule.c play.c)
else()
    add_executable(go main.c board.c display.c rule.c play.c)
endif()