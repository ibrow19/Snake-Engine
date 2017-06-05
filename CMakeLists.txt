cmake_minimum_required(VERSION 3.1)
set(PROJECT_NAME Catan)
set(CMAKE_BUILD_TYPE Release)
project(${PROJECT_NAME} C CXX)

# Compiler flags.
add_definitions(-Wall -Wextra -std=c++11)

# Include and resource directories.
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res)

# Set include directory and select files for compilation.
include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create executable.
set(EXECUTABLE_NAME "game")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Find libraries.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARY}
                                         ${SDL2_IMAGE_LIBRARIES}
                                         ${SDL2_TTF_LIBRARIES})
               
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CMAKE_BINARY_DIR})
