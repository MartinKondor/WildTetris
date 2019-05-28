#include "board.hpp"


Board::Board(Tetromino* tetrominos, int screen_height) {
    this->screen_height = screen_height;
    this->tetrominos = tetrominos;
    this->clean_up();
}

bool Board::is_free_block(int xcoord, int ycoord) {
    return true;
}


/**
 * Place tetromino to the board from it's first filled element
 * 
 * xcoord - Horizontal position in blocks
 * ycoord - Vertical position in blocks
 */
void Board::store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation) {
    Tetromino t = Tetromino(shape_type);
    t.rotate(n_of_90_degree_rotation);

    /**
     * Get the first filled x and y coordinates
     */
    int first_filled_x = 5;
    int first_filled_y = 5;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (t.pixels[i][j] == 1) {
                if (first_filled_y > i) {
                    first_filled_y = i;
                }
                if (first_filled_x > j) {
                    first_filled_x = j;
                }           
            }
        }
    }

    for (int i = first_filled_x; i < 5 - first_filled_x; i++) {
        for (int j = first_filled_y; j < 5 - first_filled_y; j++) {
            if (t.pixels[i][j] == 1) {
                this->board[xcoord + i - first_filled_x][ycoord + j - first_filled_y] = 1;
            }
        }
    }
}

void Board::delete_possible_lines() {
    
}

bool Board::is_game_over() {
    return false;
}

/**
 * Fills the board with 0s
 */
void Board::clean_up() {
    // Fill the board with free positions
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            this->board[i][j] = 0;
        }
    }
}

void Board::print() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            std::cout << this->board[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}
