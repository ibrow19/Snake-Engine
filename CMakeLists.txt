cmake_minimum_required(VERSION 3.1)
set(PROJECT_NAME Engine)
set(CMAKE_BUILD_TYPE Debug)
project(${PROJECT_NAME} C CXX)

# Cmake modules.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Find OpenGL modules.
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Find SDL2 modules.
find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find Boost modules.
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

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
target_link_libraries(${LIB_NAME} ${GLEW_LIBRARIES}
                                  ${OPENGL_LIBRARIES}
                                  ${SDL2_LIBRARY}
                                  ${SDL2_IMAGE_LIBRARIES}
                                  ${SDL2_TTF_LIBRARIES})

# Test executable for experimenting with engine.
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(TEST_EXE_SOURCES ${TEST_DIR}/main.cpp)
set(TEST_EXE_NAME "game")

add_executable(${TEST_EXE_NAME} ${TEST_EXE_SOURCES})
target_link_libraries(${TEST_EXE_NAME} ${LIB_NAME})

# Copy resources to binary directory.
set(RES_DIR ${PROJECT_SOURCE_DIR}/res)
file(COPY ${RES_DIR} DESTINATION ${PROJECT_BINARY_DIR})

# Unit tests executables.
enable_testing()
add_definitions(-DBOOST_TEST_DYN_LINK) 
add_definitions(-DBOOST_TEST_MAIN) 

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${TEST_DIR} ${TEST_DIR}/*test*.cpp)
foreach(TEST_SOURCE_FILE ${TEST_SOURCES})
    # Remove .cpp from executable name.
    string(REPLACE ".cpp" "" TEST_STEM ${TEST_SOURCE_FILE})
    string(REPLACE "/" "_" TEST_NAME ${TEST_STEM})
    add_executable(${TEST_NAME} ${TEST_DIR}/${TEST_SOURCE_FILE})
    target_link_libraries(${TEST_NAME} ${LIB_NAME}
                                       ${Boost_FILESYSTEM_LIBRARY}
                                       ${Boost_SYSTEM_LIBRARY}
                                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach(TEST_SOURCE_FILE ${TEST_SOURCES})
