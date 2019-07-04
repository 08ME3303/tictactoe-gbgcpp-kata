add_executable(tictactoe_tests main_tests.cpp test_tictactoe.cpp)
target_link_libraries(tictactoe_tests catch2 src)
set(TARGET tictactoe_tests PROPERTY CXX_STANDARD 17)

enable_testing()
add_test(NAME tictactoe_tests COMMAND tictactoe_tests)