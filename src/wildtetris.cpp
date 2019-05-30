#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <time.h>

struct Pair {
    int pair[2];
    const int operator[](const int index) {
        return pair[index];
    }
};

#include "tetromino.cpp"
#include "board.cpp"
#include "game.cpp"

using std::cout;
using std::endl;


void showinfo() {
    cout << endl;
    cout << "Keys:" << endl;
    cout << "(R)\tRotate" << endl;
    cout << "(E)\tExit" << endl;
    cout << endl;
}


int main(const int argc, const char** args) {
    Board board = Board();
    int rotation = 0;
    int xmove = 0;
    int ymove = 1;

    // throw the first tetromino
    board.throw_new_tetromino();

    while (true) {
        Sleep(200);
        system("cls");

        // showing board and info on screen
        showinfo();
        board.print();

        // check win conditions
        if (!board.is_won()) {
            cout << "Game over";
            exit(0);
        }

        // rotation key
        if (GetKeyState('R') & 0x8000) {
            rotation++;
        }

        // exit key
        if (GetKeyState('E') & 0x8000) {
            break;
        }

        board.update(rotation, xmove, ymove);  // fix
        board.remove_last_line_if_possible();
    }

    return 0;
}
