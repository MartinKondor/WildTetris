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


int main(const int argc, const char** args) {
    Game().start();
    return 0;
}
