#include "catch2/catch.hpp"
#include "tictactoe_solution.hpp"
#include <sstream>
#include <cstring>

TEST_CASE("test_can_create_position_class_instance_with_zero_zero", "[tictactoe]") {
    auto p = tictactoe::Position(0, 0);
    REQUIRE(p.to_string() == "[0,0]");
}

TEST_CASE("test_can_create_position_class_instance_with_one_two", "[tictactoe]") {
    auto p = tictactoe::Position(1, 2);
    REQUIRE(p.to_string() == "[1,2]");
}

TEST_CASE("test_create_tictactoe_with_empty_board", "[tictactoe]") {
    auto t = tictactoe::TicTacToe();

    std::string expected_board;
    expected_board += "---\n";
    expected_board += "---\n";
    expected_board += "---\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_play_o_marker_uppper_left", "[tictactoe]") {
    auto t = tictactoe::TicTacToe();

    t.play(std::string{"O"}, tictactoe::Position(0, 0));

    std::string expected_board;
    expected_board += "O--\n";
    expected_board += "---\n";
    expected_board += "---\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_play_x_marker_uppper_left_using_string_input", "[tictactoe]") {
    auto t = tictactoe::TicTacToe();

    t.play("X,0,0");

    std::string expected_board;
    expected_board += "X--\n";
    expected_board += "---\n";
    expected_board += "---\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_detect_winner_across", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"O"}, tictactoe::Position(0, 0));
    t.play(std::string{"X"}, tictactoe::Position(1, 0));
    t.play(std::string{"O"}, tictactoe::Position(0, 1));
    t.play(std::string{"X"}, tictactoe::Position(2, 0));
    t.play(std::string{"O"}, tictactoe::Position(0, 2));

    std::string expected_board;
    expected_board += "OOO\n";
    expected_board += "X--\n";
    expected_board += "X--\n";
    expected_board += "Player O wins!\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_detect_winner_vertically", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"X"}, tictactoe::Position(0, 2));
    t.play(std::string{"O"}, tictactoe::Position(1, 1));
    t.play(std::string{"X"}, tictactoe::Position(1, 2));
    t.play(std::string{"O"}, tictactoe::Position(2, 1));
    t.play(std::string{"X"}, tictactoe::Position(2, 2));

    std::string expected_board;
    expected_board += "--X\n";
    expected_board += "-OX\n";
    expected_board += "-OX\n";
    expected_board += "Player X wins!\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_detect_winner_left_to_right", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"O"}, tictactoe::Position(0, 0));
    t.play(std::string{"X"}, tictactoe::Position(0, 1));
    t.play(std::string{"O"}, tictactoe::Position(1, 1));
    t.play(std::string{"X"}, tictactoe::Position(0, 2));
    t.play(std::string{"O"}, tictactoe::Position(2, 2));

    std::string expected_board;
    expected_board += "OXX\n";
    expected_board += "-O-\n";
    expected_board += "--O\n";
    expected_board += "Player O wins!\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_detect_winner_right_to_left", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"O"}, tictactoe::Position(0, 2));
    t.play(std::string{"X"}, tictactoe::Position(0, 1));
    t.play(std::string{"O"}, tictactoe::Position(1, 1));
    t.play(std::string{"X"}, tictactoe::Position(0, 0));
    t.play(std::string{"O"}, tictactoe::Position(2, 0));

    std::string expected_board;
    expected_board += "XXO\n";
    expected_board += "-O-\n";
    expected_board += "O--\n";
    expected_board += "Player O wins!\n";

    REQUIRE(t.to_string() == expected_board);
}

TEST_CASE("test_play_same_cell_twice_throws_exception", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"O"}, tictactoe::Position(1, 1));

    REQUIRE_THROWS_AS( t.play(std::string{"X"}, tictactoe::Position(1, 1)), tictactoe::CellNotEmpty );
}

TEST_CASE("test_play_same_player_twice_throws_exception", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{"O"}, tictactoe::Position(1, 1));

    REQUIRE_THROWS_AS( t.play(std::string{"O"}, tictactoe::Position(1, 2)), tictactoe::SamePlayerTwice );
}

TEST_CASE("test_detect_tie", "[tictactoe]") {
    tictactoe::TicTacToe t;

    t.play(std::string{'O'}, tictactoe::Position(0, 0));
    t.play(std::string{'X'}, tictactoe::Position(0, 1));
    t.play(std::string{'O'}, tictactoe::Position(0, 2));
    t.play(std::string{'X'}, tictactoe::Position(1, 1));
    t.play(std::string{'O'}, tictactoe::Position(1, 0));
    t.play(std::string{'X'}, tictactoe::Position(1, 2));
    t.play(std::string{'O'}, tictactoe::Position(2, 1));
    t.play(std::string{'X'}, tictactoe::Position(2, 0));
    t.play(std::string{'O'}, tictactoe::Position(2, 2));

    std::string expected_board;
    expected_board += "OXO\n";
    expected_board += "OXX\n";
    expected_board += "XOO\n";
    expected_board += "Tie!\n";

    REQUIRE(t.to_string() == expected_board);
}


