add_library(src_solution tictactoe_solution.cpp)
target_include_directories(src_solution PUBLIC .)

add_executable(tictactoe_solution main_src_solution.cpp)
target_link_libraries(tictactoe_solution src_solution)
set(TARGET tictactoe_solution PROPERTY CXX_STANDARD 17)