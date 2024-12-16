# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(flappy_bird LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Target executable
add_executable(main ${SRC_FILES})

# Link SDL2
target_link_libraries(main SDL2)

# Specify output directory for binaries
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
