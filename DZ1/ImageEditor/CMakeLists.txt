cmake_minimum_required(VERSION 3.0.0)

project(ImageEditor)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)

link_directories(Release/lib)

add_subdirectory(tests)