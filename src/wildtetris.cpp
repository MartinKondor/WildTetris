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


void showinfo(const Board &board) {
    cout << endl;
    cout << "Keys:" << endl;
    cout << "(R)\tRotate" << endl;
    cout << "(E)\tExit" << endl;
    cout << endl;
    cout << "Score: " << board.score << endl;
    cout << endl;
}

int handle_keys(int &xmove, int &ymove, int &rotation) {
    // rotation key
    if (GetKeyState('R') & 0x8000) {
        rotation++;
    }
    // exit key
    if (GetKeyState('E') & 0x8000) {
        return 1;
    }
    if (GetKeyState(VK_DOWN) & 0x8000) {
        ymove++;
    }
    if (GetKeyState(VK_UP) & 0x8000) {
        ymove--;
    }
    if (GetKeyState(VK_LEFT) & 0x8000) {
        xmove--;
    }
    if (GetKeyState(VK_RIGHT) & 0x8000) {
        xmove++;
    }
    return 0;
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
        showinfo(board);
        board.print();

        // check win conditions
        if (!board.is_won()) {
            cout << "Game over";
            exit(0);
        }

        if (handle_keys(xmove, ymove, rotation) == 1) {
            break;
        }

        board.update(rotation, xmove, ymove);
        board.remove_last_line_if_possible();
    }

    return 0;
}
