cmake_minimum_required(VERSION 3.1)
set(PROJECT_NAME Engine)
set(CMAKE_BUILD_TYPE Debug)
project(${PROJECT_NAME} C CXX)


# Cmake modules.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Find SDL modules.
find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find Boost modules.
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Compiler flags.
add_definitions(-Wall -Wextra -std=c++11)

# Include directory for library.
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
include_directories(${INCLUDE_DIR})

# Source files for library.
file(GLOB_RECURSE LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create library.
set(LIB_NAME "Engine")
add_library(${LIB_NAME} ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${SDL2_LIBRARY}
                                  ${SDL2_IMAGE_LIBRARIES}
                                  ${SDL2_TTF_LIBRARIES})


# Test executable for experimenting with engine.
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(TEST_EXE_SOURCES ${TEST_DIR}/testmain.cpp)
set(TEST_EXE_NAME "game")

add_executable(${TEST_EXE_NAME} ${TEST_EXE_SOURCES})
target_link_libraries(${TEST_EXE_NAME} ${LIB_NAME})


# Unit tests.
enable_testing()


# Test files.
#file(GLOB_RECURSE TESTS ${PROJECT_SOURCE_DIR}/test/*.cpp)
#
#
#include_directories(${SDL2_INCLUDE_DIR}
#                    ${SDL2_IMAGE_INCLUDE_DIR}
#                    ${SDL2_TTF_INCLUDE_DIR})
#target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARY}
#                                         ${SDL2_IMAGE_LIBRARIES}
#                                         ${SDL2_TTF_LIBRARIES})
               
# Install target
#install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CMAKE_BINARY_DIR})
