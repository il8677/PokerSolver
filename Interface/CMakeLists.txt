cmake_minimum_required(VERSION 3.11)
project(Interface)

include_directories(src)

include_directories(vendor)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_executable(PokerInterface ${SOURCES})

target_link_libraries(PokerInterface SolverLib)