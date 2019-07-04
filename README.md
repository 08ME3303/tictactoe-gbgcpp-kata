# tictactoe-gbgcpp-kata
Code kata for Gothenburg C++ Meetup created by Jacob Mossberg

Goal is to create a TicTacToe class which allows user to run a console based Tic-tac-toe game. 
The players are denoted by 'X' and 'O'. These markers are placed on a board. 

We start with an empty board:

    ---
    ---
    ---
    
Player `X` puts a marker in the upper left corner:

    X--
    ---
    ---
    
Player `O` puts a marker in the upper right corner:

    X-O
    ---
    ---  

After some more iterations the game board looks like this:

    XXO
    -XX
    -OO

Player `O` makes a winning move by putting a marker in the lower left corner:

    XXO
    -XX
    OOO
    Player O wins!

## Folder structure
* `3rdparty` contains the [Catch2](https://github.com/catchorg/Catch2) test frame work

* `src` contains the code.
  * `src/tictactoe.hpp` and `src/tictactoe.cpp` contain the code to run the game.
  * The final console application is run from `src/main_src.cpp.`.
  
* `tests` contains the tests. 

## Tools and Environment
* C++ 17
* CMake 3.14.0
* Visual Studio 2019
* Catch2 

## Coding kata

Starting the code kata, we develop the `TicTacToe` class with a helper `Position` class. 

### Step 1
A helper class named `Position` that is used to specify a position on the game board using x- and y-coordinates.

        012 y-axis 
      0 ---
      1 ---
      2 ---
    x-axis 
    
Putting a `X` mark at `[x=1, y=0]`:

        012 y-axis
      0 -0-
      1 X--
      2 ---
    x-axis    

And the following test to `test_tictactoe.cpp`:

    TEST_CASE("test_can_create_position_class_instance_with_zero_zero", "[tictactoe]") {
        auto p = tictactoe::Position(0, 0);
        REQUIRE(p.to_string() == "[0,0]");
    }       

### Step 2

Now making `test_can_create_position_class_instance_with_zero_zero` pass by adding a a class named `Position` to `tictactoe.hpp` within the `tictactoe` namespace.

    class Position {
    public:
        Position(int x, int y);
        std::string to_string() const;
    };

And then adding the following definitions to `tictactoe.cpp` within the `tictactoe` namespace:

    Position::Position(int x, int y) {}

    std::string Position::to_string() const {
        return std::string{"[0,0]"};
    } 

### Step 3

A new test to verifies that the `Position` class accepts other coordinate values than `0, 0`.

Code:

    auto p = tictactoe::Position(1,2)
    std::cout << p.to_string() << std::endl;
    
Output:

    [1,2] 
    

### Step 4

Let's continue and start working on the class `TicTacToe`. We want the `TicTacToe` class to maintain an updated view of the game board that can be retrieved by running the `to_string()` method on an instance of the class. 

Add a test to verify that we can create an instance of `TicTacToe` and that it returns the following string representation of an empty board:

    TEST_CASE("test_create_tictactoe_with_empty_board", "[tictactoe]") {
        auto t = tictactoe::TicTacToe();
    
        std::string expected_board;
        expected_board += "---\n";
        expected_board += "---\n";
        expected_board += "---\n";
    
        REQUIRE(t.to_string() == expected_board);
    }
   
   
### Step 5

The `TicTacToe` class implements a `play` method which accepts an argument set to `X` or `O` and also a position argument. 

    TEST_CASE("test_play_o_marker_uppper_left", "[tictactoe]") {
        auto t = tictactoe::TicTacToe();
    
        t.play(std::string{"O"}, tictactoe::Position(0, 0));
    
        std::string expected_board;
        expected_board += "O--\n";
        expected_board += "---\n";
        expected_board += "---\n";
    
        REQUIRE(t.to_string() == expected_board);
    }


### Step 6
The `TicTactoe` class implements an overload of the `play` method that accepts a string as input. This can be used later when running the Tic-tac-toe game in the console.

Add the following test:

    TEST_CASE("test_play_x_marker_uppper_left_using_string_input", "[tictactoe]") {
        auto t = tictactoe::TicTacToe();
    
        t.play("X,0,0");
    
        std::string expected_board;
        expected_board += "X--\n";
        expected_board += "---\n";
        expected_board += "---\n";
    
        REQUIRE(t.to_string() == expected_board);
    }
    

### Step 7

`TicTacToe` class checks if we have a winner across the board and prints out the winner in it's string representation. 

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

### Step 8

`TicTacToe` class checks if we have a winner vertically on the board and prints out the winner in it's string representation.

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

### Step 9

Finally `TicTacToe` finds winners both on left-to-right diagonal and right-to-left diagonal on the board and prints out the winner in its string representation.

Corresponding test is added to test+tictactoe.cpp

### Step 10
The game throws an exception if the same player tries to play two times in a row or if the same positions is being played twice.

### Step 11

The `TicTacToe` class recognizes a tie, i.e. when the board is full and there is no player with three marks in a row (up, down, across or diagonally).

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

### Step 12

Using the TicTacToe class to run a console application. 

Running the application looks like this:

    tictactoe
    
    ---
    ---
    ---
    Enter move (e.g. X,0,1): X,0,0
    
    X--
    ---
    ---
    Enter move (e.g. X,0,1): O,0,1
    
    XO-
    ---
    ---
    Enter move (e.g. X,0,1): X,2,2
    
    XO-
    ---
    --X
    Enter move (e.g. X,0,1): O,1,1
    
    XO-
    -O-
    --X
    Enter move (e.g. X,0,1): X,1,0
    
    XO-
    XO-
    --X
    Enter move (e.g. X,0,1): O,2,1
    
    XO-
    XO-
    -OX
    Player O wins!
