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
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find Boost modules.
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

# Find rapidxml.
find_package(RapidXML REQUIRED)

# Compiler flags.
add_definitions(-Wall -Wextra -std=c++11)

# Include directories for library.
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/inc 
                 ${GLEW_INCLUDE_DIR}
                 ${OpenGL_INCLUDE_DIRS}
                 ${SDL2_INCLUDE_DIR}
                 ${SDL2_IMAGE_INCLUDE_DIRS}
                 ${RAPIDXML_INCLUDE_DIR})
include_directories(${INCLUDE_DIRS})

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

# Demo executable for experimenting with engine.
set(DEMO_DIR ${PROJECT_SOURCE_DIR}/demo)
file(GLOB_RECURSE DEMO_SOURCES ${DEMO_DIR}/*.cpp)
set(DEMO_NAME "demo")
include_directories(${DEMO_DIR})

add_executable(${DEMO_NAME} ${DEMO_SOURCES})
target_link_libraries(${DEMO_NAME} ${LIB_NAME})

# Copy resources to binary directory.
set(RES_DIR ${PROJECT_SOURCE_DIR}/res)
file(COPY ${RES_DIR} DESTINATION ${PROJECT_BINARY_DIR})

# Unit tests executables.
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
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
