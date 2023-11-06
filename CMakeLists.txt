cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

project(GeneticAlgorithm)

add_executable(GA_APP main.cpp helpers.cpp)

#TODO add subdirs and include dirs
include_directories(${CMAKE_SOURCE_DIR}/includes)

add_subdirectory(${CMAKE_SOURCE_DIR}/ConcreteGA)

# target_include_directories(BufferApp )
message("HELLO")
message("${CMAKE_SOURCE_DIR}")

target_link_libraries(GA_APP GA_LIB)
