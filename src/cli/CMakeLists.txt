add_library(cli
    cli_info.cpp
    cli_parse_context.cpp
    cli_parser.cpp
    cli_validate.cpp
)

target_include_directories(cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
