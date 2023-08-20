cmake_minimum_required(VERSION 3.10)

project(Inverted_Pendulum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS  "-std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS=ON)

list(APPEND CMAKE_PREFIX_PATH $ENV{MATHLIB_DIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{PUBSUBLIB_DIR})

find_package(mathlib CONFIG REQUIRED)
find_package(PubSub CONFIG REQUIRED)

add_subdirectory("SW")
add_subdirectory("Sim")
add_subdirectory("Runner")