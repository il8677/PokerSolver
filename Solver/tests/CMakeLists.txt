cmake_minimum_required(VERSION 3.11)

find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_executable(SolverTest ${SOURCES})
target_link_libraries(SolverTest SolverLib Catch2::Catch2WithMain)
