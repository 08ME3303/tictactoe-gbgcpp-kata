#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "tictactoe_solution.hpp"

namespace tictactoe {

    std::vector<std::string> split_string(const std::string &move, const char delimiter) {
        std::stringstream ss{move};
        std::vector<std::string> elements;
        for (std::string elem; std::getline(ss, elem, delimiter);) {
            elements.push_back(elem);
        }
        return elements;
    }

    // class Position

    Position::Position(int x, int y) : _x{x}, _y{y} {}

    std::string Position::to_string() const {
        std::stringstream ss;
        ss << "[" << _x << "," << _y << "]";
        return ss.str();
    }

    // class TicTacToe - public

    TicTacToe::TicTacToe() : _board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY_CELL)), _last_player{""} {}

    void TicTacToe::play(std::string player, Position p) {
        if (_board[p._x][p._y] != EMPTY_CELL) {
            throw CellNotEmpty();
        }
        if (player == _last_player) {
            throw SamePlayerTwice();
        }
        _last_player = player;
        _board[p._x][p._y] = player[0];
    }

    void TicTacToe::play(std::string move) {
        std::vector<std::string> move_elements = split_string(move, ',');

        std::string player{move_elements[0]};
        int x{std::stoi(move_elements[1])};
        int y{std::stoi(move_elements[2])};
        auto pos = tictactoe::Position(x,y);

        play(player, pos);
    }

    std::string TicTacToe::to_string() const {
        std::string board;

        for (const auto &row : _board) {
            for (const auto &elem : row) {
                board += elem;
            }
            board += "\n";
        }

        auto player = winner(_board);
        if (player != NO_WINNER) {
            board += "Player ";
            board += player;
            board += " wins!";
            board += "\n";
        } else if (is_board_full(_board)) {
            board += "Tie!\n";
        }

        return board;
    }

    // class TicTacToe - private

    const char TicTacToe::EMPTY_CELL{'-'};
    const char TicTacToe::NO_WINNER{0};
    const int TicTacToe::BOARD_SIZE{3};

    char TicTacToe::winner(TicTacToe::GameBoard board) {
        std::vector<char (*)(TicTacToe::GameBoard)> winner_functions{TicTacToe::winner_across,
                                                                     TicTacToe::winner_vertical,
                                                                     TicTacToe::winner_diagonals};

        for (auto winner_function : winner_functions) {
            auto player = winner_function(board);
            if (player != NO_WINNER) {
                return player;
            }
        }

        return NO_WINNER;
    }

    bool TicTacToe::is_board_full(TicTacToe::GameBoard board) {
        for (const auto &row : board) {
            bool any_empty_cell = std::any_of(std::begin(row),
                                              std::end(row),
                                              [](auto &cell) { return cell == EMPTY_CELL; });
            if (any_empty_cell) {
                return false;
            }
        }
        return true;
    }

    TicTacToe::GameBoard TicTacToe::transpose_board(TicTacToe::GameBoard board) {
        TicTacToe::GameBoard transposed_board(board.size(), std::vector<char>(board.size(), EMPTY_CELL));

        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board.size(); y++) {
                transposed_board[y][x] = board[x][y];
            }
        }

        return transposed_board;
    }

    char TicTacToe::winner_vertical(TicTacToe::GameBoard board) {
        return TicTacToe::winner_across(TicTacToe::transpose_board(board));
    }

    char TicTacToe::winner_in_cells(std::vector<char> cells) {

        auto any_empty_cell = std::any_of(std::begin(cells), std::end(cells),
                                          [](auto &cell) { return cell == EMPTY_CELL; });

        if (any_empty_cell) {
            return NO_WINNER;
        }

        auto all_equal = std::all_of(std::begin(cells),
                                     std::end(cells),
                                     [&cells](auto &cell) { return cell == cells.front(); });

        if (all_equal) {
            return cells.front();
        }

        return NO_WINNER;
    }

    char TicTacToe::winner_diagonals(TicTacToe::GameBoard board) {
        auto max_index = board.size() - 1;

        std::vector<char> diagonal_left_to_right;
        for (int i = 0; i <= max_index; i++) {
            auto x = i;
            auto y = i;
            diagonal_left_to_right.push_back(board[x][x]);
        }

        std::vector<char> diagonal_right_to_left;
        for (int i = 0; i <= max_index; i++) {
            auto x = i;
            auto y = max_index - x;
            diagonal_right_to_left.push_back(board[x][y]);
        }

        TicTacToe::GameBoard diagonals = {diagonal_left_to_right, diagonal_right_to_left};

        for (auto &diagonal : diagonals) {
            auto winner = winner_in_cells(diagonal);
            if (winner != NO_WINNER) {
                return winner;
            }
        }

        return NO_WINNER;
    }

    char TicTacToe::winner_across(TicTacToe::GameBoard board) {
        char winner{NO_WINNER};
        for (const auto &row : board) {
            winner = winner_in_cells(row);
            if (winner != NO_WINNER) { break; }
        }
        return winner;
    }
}