cmake_minimum_required(VERSION 3.10)
project(osm-floydwarshall)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h" "src/*.hpp")

add_executable(osm-floydwarshall ${SRC})
