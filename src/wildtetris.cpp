#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <time.h>
// #include <windows.h>

struct Pair {
    int pair[2];
    const int operator[](const int index) {
        return pair[index];
    }
};

#include "tetromino.cpp"
#include "board.cpp"

using namespace std;

int main(const int argc, const char** args) {
    Board board = Board();

    // throw the first tetromino
    board.throw_new_tetromino();

    int iter = 0,
        rotation = 0,
        xmove = 0,
        ymove = 1;

    while (iter < 1) {
        // Sleep(500);

        board.print();
        cout << endl;

        try {
            board.update(rotation, xmove, ymove);
        }
        catch (const char* err) {
            if (err == "out of width" || err == "out of height") {
                board.restore_board();  // abord changes on the board
                board.throw_new_tetromino();
            }
            else {
                cout << "Error: " << err << endl;
            }
        }
        iter++;
    }

    return 0;
}
