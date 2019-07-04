#include <iostream>
#include <tictactoe.hpp>

int main(int argc, char* argv[]) {
    std::cout << "Tic-tac-toe\n";
	tictactoe::TicTacToe new_game;
	std::string out = new_game.to_string();
	std::cout << out << std::endl;
	std::string stat = out.substr(out.length() - 6);
	std::string input;
	while (stat != "wins!\n") {
		std::cout << "Enter to play, eg 'X,0,0': ";
		std::getline(std::cin, input);
		std::cout << input << std::endl;
		new_game.play(input);
		out = new_game.to_string();
		std::cout << out << std::endl;
		stat = out.substr(out.length() - 6);
	}
    return 0;
}
