cmake_minimum_required(VERSION 2.8)
project(GRAPPA CXX)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
file(GLOB sources src/*.cpp)
if(UNIX AND APPLE)
    add_definitions(-Wall -O3 -g)
    find_package(glut)
    find_package(opengl)
    add_executable(GRAPPA ${sources})
    target_link_libraries(GRAPPA ${GLUT_LIBRARY} ${OPENGL_LIBRARY} pthread)
elseif(UNIX AND NOT APPLE)
    add_definitions(-w -O3)
    add_executable(GRAPPA ${sources})
    target_link_libraries(GRAPPA glut GLU GL Xmu Xi Xext X11 m pthread)
endif()
