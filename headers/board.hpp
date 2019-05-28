/*---------------------------------------------------------------

The Board, where each tetromino is stored,
and the collusion detection takes place.

---------------------------------------------------------------*/
#ifndef _BOARD_
#define _BOARD_

#include "tetromino.hpp"

#define BOARD_HEIGHT 20  // in blocks
#define BOARD_WIDTH 10


class Board {
    public:
    Board(Tetromino* shapes, int screen_height);
    bool is_free_block(int xcoord, int ycoord);
    void store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation);
    void delete_possible_lines();
    bool is_game_over();
    void print();

    private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    int screen_height;
    Tetromino* tetrominos;

    void clean_up();
};

#endif
