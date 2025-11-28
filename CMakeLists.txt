cmake_minimum_required(VERSION 3.28.3)

project(CLI LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_subdirectory(src)
add_subdirectory(apps)
