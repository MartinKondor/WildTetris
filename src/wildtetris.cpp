#include <iostream>
#include <stdlib.h>
#include <vector>
// #include <windows.h>

struct Pair {
    int pair[2];
};

#include "tetromino.cpp"
#include "board.cpp"

using namespace std;

int main(const int argc, const char** args) {
    Board board = Board();

    // padding to the center of the board
    int xpad_to_center = BOARD_WIDTH / 2;

    board.store_tetromino(0, 0, 'L', 0);
    board.update(2, 0, 1);
    board.print();

    return 0;
}
