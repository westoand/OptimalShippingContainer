cmake_minimum_required(VERSION 3.14)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Project4 WestonAssignment4.cpp OptimalContainer.cpp)

target_link_libraries(Project4 ${Boost_LIBRARIES})