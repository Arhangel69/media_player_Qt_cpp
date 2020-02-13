cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(NAMESPACE medpl_pr)
set(COMPONENT debug)
project(${NAMESPACE}_${COMPONENT}
    VERSION 1.0.0
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

add_executable(${NAMESPACE}::${COMPONENT} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

find_package(medpl_core 1.0.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} medpl_pr::core)
