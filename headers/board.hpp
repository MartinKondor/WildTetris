/*---------------------------------------------------------------

The Board, where each tetromino is stored,
and the collusion detection takes place.

---------------------------------------------------------------*/
#ifndef _BOARD_
#define _BOARD_

#include "tetromino.hpp"

#define BOARD_HEIGHT 11  // in blocks
#define BOARD_WIDTH 7


class Board {
    public:
    std::vector<Tetromino> tetrominos;
    std::vector<Tetromino> prev_tetrominos;
    int prev_board[BOARD_HEIGHT][BOARD_WIDTH];
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int tetromino_id;

    /**
    * The active or falling tetroino's id
    */
    int current_tetromino_id;

    Board();
    
    /**
    * Determine if the block is free from tetrominos
    */
    bool is_free_block(int xcoord, int ycoord) throw (const char*);
    
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
    int store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation) throw (const char*);
    void print();

    /**
    * Fills the board with 0s
    */
    void clean_up();
    int get_new_tetromino_id();

    /**
    * This is where the current tetromnio starts to fall
    */
    void update(int rotation, int xmove, int ymove);

    /**
    * Seaches for and retruns the given id'd tetromino
    */
    Tetromino get_tetromino_by_id(int id);
    void draw_tetromino(int xcoord, int ycoord, Tetromino t) throw (const char*);
    void throw_new_tetromino();
    void save_board();
    void restore_board();
};

#endif
