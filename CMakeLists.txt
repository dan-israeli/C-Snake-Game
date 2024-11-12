cmake_minimum_required(VERSION 3.21)
project(SnakeGameProject C)

set(CMAKE_C_STANDARD 23)

# Include header files
include_directories(include)

# Collect all source files
file(GLOB SOURCES "src/*.c" "main.c")

# Add the executable
add_executable(SnakeGameProject ${SOURCES})
