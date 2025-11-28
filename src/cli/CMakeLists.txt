add_library(cli cli_info.cpp cli_validate.cpp cli.cpp)
target_include_directories(cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
