#include <iostream>
#include "tetromino.cpp"
#include "board.cpp"

using namespace std;


int main(const int argc, const char** args) {
    Tetromino* container = {};
    Board board = Board(container, 20);

    board.store_tetromino(0, 0, 'T', 0);
    board.print();

    return 0;
}
