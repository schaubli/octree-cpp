
# Define project properties
cmake_minimum_required(VERSION 3.10)
project(octree-cpp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Add library
add_library(octree STATIC 
${CMAKE_SOURCE_DIR}/src/octree.cpp
${CMAKE_SOURCE_DIR}/src/octree.hpp
${CMAKE_SOURCE_DIR}/src/point.cpp
${CMAKE_SOURCE_DIR}/src/point.hpp
${CMAKE_SOURCE_DIR}/src/aabb.cpp
${CMAKE_SOURCE_DIR}/src/aabb.hpp
)
target_include_directories(octree PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Add main executable
add_executable(octree-cpp main.cpp)

# Link libraries to executable
target_link_libraries(octree-cpp PRIVATE octree)
