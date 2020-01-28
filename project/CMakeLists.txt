cmake_minimum_required(VERSION 3.0.0)
project(oop_pr)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    source/include
    source/libsrc/include/concepts
    source/libsrc/include/tss
    source/libsrc/include/util
)

add_executable(oop_pr 
    source/oop_pr.cpp 
    source/implementation/Compiler.cpp
    source/implementation/Machine.cpp
    source/implementation/Memory.cpp
    source/implementation/Operation.cpp
    source/implementation/Config.cpp
)

target_link_libraries(oop_pr ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSimulationEngine.so)
