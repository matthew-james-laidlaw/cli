add_executable(unit_tests test_cli.cpp)
target_link_libraries(unit_tests cli GTest::gtest_main)
