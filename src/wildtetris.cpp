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

    while (iter < 6) {
        // Sleep(500);

        board.print();
        cout << endl;

        board.remove_last_line_if_possible();
        
        if (!board.is_won()) {
            cout << "Game over";
            exit(0);
        }

        board.update(rotation, xmove, ymove);
        iter++;
    }

    return 0;
}
