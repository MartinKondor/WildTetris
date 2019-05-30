/*---------------------------------------------------------------

The Board, where each tetromino is stored,
and the collusion detection takes place.

---------------------------------------------------------------*/
#ifndef _BOARD_
#define _BOARD_

#include "tetromino.hpp"

#define BOARD_HEIGHT 14  // in blocks
#define BOARD_WIDTH 10


class Board {
    public:
    int prev_board[BOARD_HEIGHT][BOARD_WIDTH];
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    std::vector<Tetromino> tetrominos;
    std::vector<Tetromino> prev_tetrominos;
    int tetromino_id;
    int score;
    int game_is_over;

    /**
    * The active or falling tetroino's id
    */
    int current_tetromino_id;

    Board();
    const void print();

    /**
    * Throw a new playable tetromino from the top
    */
    const void throw_new_tetromino();

    /**
     * Place tetromino to the board from it's first filled element
     *
     * xcoord - Horizontal position in blocks
     * ycoord - Vertical position in blocks
     *
     * The x, y coordinate center is (0, 0) the left upper
     * corner of the this->board matrix
     *
     * returns the tetromino's id
     */
    const int store_tetromino(int xcoord, int ycoord, char shape_type, int rotation);

    /**
    * Determine if the block is free from tetrominos
    */
    const bool is_free_block(int xcoord, int ycoord);
    const void restore_board();

    /**
    * Fills the board with 0s
    */
    const void clean_up();
    const int get_new_tetromino_id();

    /**
    * This is where the current tetromnio starts to fall
    */
    const void update(int rotation, int xmove, int ymove);
    const void draw_tetromino(int xcoord, int ycoord, Tetromino &t);
    const void save_board();
    const void remove_last_line_if_possible();

    /**
     * Checks if the player can continue or lose the game
     * false = losing
     * true = continue
     */
    const bool is_won();
};

#endif
