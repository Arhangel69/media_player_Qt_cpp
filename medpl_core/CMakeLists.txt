cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(NAMESPACE medpl_pr)
set(COMPONENT core)
project(${NAMESPACE}-${COMPONENT}
VERSION 1.0.0
LANGUAGES CXX
)

#find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Multimedia)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(${PROJECT_NAME}
include/${NAMESPACE}/mainwindow.hpp
src/mainwindow.cpp
src/mainwindow.ui
)

add_library(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")


include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Multimedia)
