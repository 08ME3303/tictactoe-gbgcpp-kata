#include <iostream>
#include "tictactoe_solution.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Tic-tac-toe\n";
    tictactoe::TicTacToe t;

    while(true) {
        std::cout << "\nBoard\n";

        std::cout << t.to_string();

        if(t.to_string().find("wins") != std::string::npos) {
            break;
        }

        if(t.to_string().find("Tie") != std::string::npos) {
            break;
        }

        std::cout << "Enter move (e.g. X,0,1): ";
        std::string move;
        std::cin >> move;

        t.play(move);
    }
    return 0;
}