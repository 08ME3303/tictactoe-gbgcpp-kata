#ifndef TICTACTOE_SOLUTION_HPP
#define TICTACTOE_SOLUTION_HPP

#include <ostream>
#include <vector>

namespace tictactoe {
    std::vector<std::string> split_string(const std::string &move, const char delimiter);

    class Position {
    public:
        Position(int x, int y);

        std::string to_string() const;

        int _x;
        int _y;
    };

    class CellNotEmpty : public std::exception {};
    class SamePlayerTwice : public std::exception {};

    class TicTacToe {
    public:
        TicTacToe();
        void play(std::string player, Position p);
        void play(std::string move);
        std::string to_string() const;

    private:
        using GameBoard = std::vector<std::vector<char>>;
        GameBoard _board;
        std::string _last_player;

        static const int BOARD_SIZE;
        static const char EMPTY_CELL;
        static const char NO_WINNER;

        static char winner(TicTacToe::GameBoard board);
        static bool is_board_full(TicTacToe::GameBoard board);
        static char winner_across(TicTacToe::GameBoard board);
        static char winner_vertical(TicTacToe::GameBoard board);
        static char winner_diagonals(TicTacToe::GameBoard board);
        static TicTacToe::GameBoard transpose_board(TicTacToe::GameBoard board);
        static char winner_in_cells(std::vector<char> cells);
    };
}

#endif //TICTACTOE_SOLUTION_HPPs
