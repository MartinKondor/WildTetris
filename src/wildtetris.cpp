#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <windows.h>

#include "rlutil.h"

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

const void showinfo(const Board &board) {
    cout << endl;
    cout << "Keys:" << endl;
    cout << "(R)\tRotate" << endl;
    cout << "(E)\tExit" << endl;
    cout << endl;
    cout << "Score: " << board.score << endl;
    cout << endl;
}

const int handle_keys(int &xmove, int &ymove, int &rotation) {
    // exit key
    if (GetAsyncKeyState('E') & 0x8000) {
        return 1;
    }
    // rotation key
    if (GetAsyncKeyState('R') & 0x8000) {
        rotation++;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        ymove++;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        ymove--;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        xmove--;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        xmove++;
    }
    return 0;
}


int main(const int argc, const char** args) {
    rlutil::saveDefaultColor();

    Board board = Board();
    int rotation = 0;
    int xmove = 0;
    int ymove = 1;

    // throw the first tetromino
    board.throw_new_tetromino();

    while (true) {
        Sleep(200);
        if (handle_keys(xmove, ymove, rotation) == 1) {
            break;
        }

        system("\"cls\"");
        showinfo(board);
        board.print();

        // check win conditions
        if (!board.is_won()) {
            cout << "Game over";
            exit(0);
        }

        board.update(rotation, xmove, ymove);
        board.remove_last_line_if_possible();

        xmove = 0;
        ymove = 1;
        rotation = 0;
    }

    return 0;
}
