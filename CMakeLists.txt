cmake_minimum_required(VERSION 3.28.3)

project(CLI LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

FIND_PACKAGE(GTest CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(apps)
