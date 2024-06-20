cmake_minimum_required(VERSION 3.25)
project(MineC LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE MineC_HEADERS "src/*.h")
file(GLOB_RECURSE MineC_SOURCES "src/*.c")

add_executable(MineC ${MineC_HEADERS} ${MineC_SOURCES})

target_compile_options(MineC PRIVATE -Wall -Wextra -Wpedantic)
