cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(MediaPlayer
    VERSION 1.0.0
    LANGUAGES CXX
)

set(SUBPROJECTS
    medpl_core
    medpl_debug
)

macro(find_package)
    if(NOT "${ARGV0}" IN_LIST SUBPROJECTS)
        _find_package(${ARGV})
    endif()
endmacro()

foreach(subdir IN LISTS SUBPROJECTS)
    add_subdirectory(${subdir})
endforeach()
