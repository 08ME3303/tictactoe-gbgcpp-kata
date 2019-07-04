#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include<string>
#include<iterator>
#include<vector>
#include<iostream>

namespace tictactoe {
	bool always_true();

	class TicTacToe;

	class Position {
	public:
		Position(int x, int y);
		std::string to_string() const;
		friend TicTacToe;

	private:
		int _x;
		int _y;
	};

	class TicTacToe {
	public:
		std::vector<std::vector<char>> playboard;
		int size_of_board = 3;
		std::string board;
		TicTacToe() {
			for (int i = 0; i < size_of_board; i++) {
				std::vector<char> temp;
				for (int j = 0; j < size_of_board; j++) {
					temp.push_back('-');
				}
				playboard.push_back(temp);
			}
		}

		std::string to_string() const {
			std::string printer, temp;
			for (int i = 0; i < size_of_board; i++) {
				char x = playboard[i][0];
				int count = 0;
				for (int j = 0; j < size_of_board; j++) {
					printer += playboard[i][j];
					if (x == playboard[i][j] && x != '-') count++;
				}
				if (count == 3) {
					temp = "Player ";
					temp += x;
					temp += " wins!\n";
				}
				printer += '\n';
			}

			for (int j = 0; j < size_of_board; j++) {
				char x = playboard[0][j];
				int count = 0;
				for (int i = 0; i < size_of_board; i++) {
					if (x == playboard[i][j] && x != '-') count++;
				}
				if (count == 3) {
					temp = "Player ";
					temp += x;
					temp += " wins!\n";
				}
			}
			char x = playboard[0][0];
			int count = 0;
			for (int i = 0; i < size_of_board; i++) {
				if (x == playboard[i][i] && x != '-') count++;
			}
			if (count == 3) {
				temp = "Player ";
				temp += x;
				temp += " wins!\n";
			}
			x = playboard[0][2];
			count = 0;
			for (int i = size_of_board - 1; i >= 0; i--) {
				if (x == playboard[size_of_board - i - 1][i] && x != '-') count++;
			}
			if (count == 3) {
				temp = "Player ";
				temp += x;
				temp += " wins!\n";
			}

			printer += temp;
			return printer;
		};

		void play(char inp, Position a) {
			int x = a._x;
			int y = a._y;
			int num_x = 0, num_o = 0;
			for (auto i = playboard.begin(); i != playboard.end(); ++i) {
				for (auto j = i->begin(); j != i->end(); ++j) {
					if (*j == 'X') {
						num_x++;
					}
					else {
						if (*j == 'O') num_o++;
					}
				}
			}
			try {
				if (abs(num_x - num_o) == 2) throw 0;
				if (playboard[x][y] != '-') throw playboard[x][y] ;
			}
			catch (char x) {
				std::cerr << "CellNotEmpty\n";
			}
			catch (int x) {
				std::cerr << inp << "has already played\n";
			}
			if (playboard[x][y] == '-') playboard[x][y] = inp;
		}

		void play(std::string inp) {
			int x = std::stoi(inp.substr(2, 1));
			int y = std::stoi(inp.substr(4, 1));
			play(inp[0], Position(x, y));
		}
	};

};

#endif //TICTACTOE_HPP
