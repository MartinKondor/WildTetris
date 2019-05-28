/*---------------------------------------------------------------

All the actual tests for this porject.

Each test returns a character, if the character is "o" it means
the test were fine, else it returns an "x".

---------------------------------------------------------------*/
#include <iostream>
#include "../src/tetromino.cpp"

char testTetrominoPixels(Tetromino t) {
    if (t.pixels[1][2] == 1 && t.pixels[2][2] == 1;
        t.pixels[3][2] == 1 && t.pixels[4][2] == 1) {
        return 'o';
    }
    return 'x';
}


int main(const int argc, const char** args) {
    std::cout << "Testing WildTetris" << std::endl;

    Tetromino t = Tetromino('I');
    std::cout << "Tetromino.pixels: " << testTetrominoPixels(t) << std::endl;
    t.rotate(1);
    std::cout << "Tetromino.rotate(1): " << "x" << std::endl;
    


    return 0;
}
