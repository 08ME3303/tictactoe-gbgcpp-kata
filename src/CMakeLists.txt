add_library(src tictactoe.cpp)
target_include_directories(src PUBLIC .)

add_executable(tictactoe main_src.cpp)
target_link_libraries(tictactoe src)
set(TARGET tictactoe PROPERTY CXX_STANDARD 17)
