cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.36.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

project(kalmanfilter VERSION 1.0)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})

add_subdirectory(plots)
target_include_directories(${PROJECT_NAME} PUBLIC plots/)
target_link_directories(${PROJECT_NAME} PRIVATE plots/)
target_link_libraries(${PROJECT_NAME} Plots)