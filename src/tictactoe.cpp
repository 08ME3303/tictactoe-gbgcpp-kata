#include "tictactoe.hpp"

namespace tictactoe {

	bool always_true() {
		return true;
	}

	Position::Position(int x, int y) : _x{ x }, _y{ y }{};

	std::string Position::to_string() const {
		std::string s;
		s = "[" + std::to_string(_x) + "," + std::to_string(_y) + "]";
		return s;
	}
}

void player() {
	tictactoe::TicTacToe new_game;
	std::string out = new_game.to_string();
	std::cout << out << std::endl;
}
