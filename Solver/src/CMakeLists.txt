cmake_minimum_required(VERSION 3.11)
project(SolverLib)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_library(SolverLib STATIC ${SOURCES})
set_target_properties(SolverLib PROPERTIES LINKER_LANGUAGE CXX)
