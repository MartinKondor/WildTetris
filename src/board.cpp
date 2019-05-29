#include "board.hpp"


Board::Board() {
    this->tetrominos = {};
    this->tetromino_id = 0;
    this->current_tetromino_id = 0;
    this->clean_up();
}

void Board::store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation) {
    if (!this->is_free_block(xcoord, ycoord)) {
        std::cout << "(" << ycoord << ", " << xcoord << ") is not a free position" << std::endl;
        exit(1);
    }

    // creating and rotating tetromino object
    Tetromino t = Tetromino(shape_type, xcoord, ycoord, this->get_new_tetromino_id());
    t.rotate(n_of_90_degree_rotation);

    this->draw_tetromino(xcoord, ycoord, t);

    this->tetrominos.push_back(t);
    this->current_tetromino_id = t.id;
}

void Board::draw_tetromino(int xcoord, int ycoord, Tetromino t) {
    Pair pads = t.get_paddings();
    int xpad = pads.pair[0],
        ypad = pads.pair[1];

    for (int i = 0; i < 5; i++) {  // place tetromino to the board
        for (int j = 0; j < 5; j++) {
            if (t.pixels[i][j] == 1) {
                int newx = xcoord + j - xpad,
                    newy = ycoord + i - ypad;

                if (!this->is_free_block(newx, newy)) {
                    std::cout << "(" << newy << ", " << newx << ") is not a free position" << std::endl;
                    exit(1);
                }
                this->board[newy][newx] = 1;
            }
        }
    }
}

bool Board::is_free_block(int xcoord, int ycoord) {
    if (xcoord > BOARD_WIDTH || ycoord > BOARD_HEIGHT) {
        std::cout << "(" << xcoord << ", " << ycoord << ") invalid position, cannot fit to the table" << std::endl;
        exit(1);
    }
    return this->board[ycoord][xcoord] == 0;
}


void Board::clean_up() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = 0;
        }
    }
}

void Board::print() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            std::cout << this->board[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

int Board::get_new_tetromino_id() {
    return this->tetromino_id++;
}

Tetromino Board::get_tetromino_by_id(int id) {
    for (int i = 0; i < this->tetrominos.size(); i++) {
        if (this->tetrominos[i].id == id) {
            return this->tetrominos[i];
        }
    }
    return Tetromino('Q', -1, -1, -1);
}

void Board::update(int rotation, int xmove, int ymove) {
    if (rotation == 0 && xmove == 0 && ymove == 0) {
        return;
    }

    this->clean_up();

    for (int i = 0; i < this->tetrominos.size(); i++) {
        if (this->current_tetromino_id == i) {
            this->tetrominos[i].xpos += xmove;
            this->tetrominos[i].ypos += ymove;
            this->tetrominos[i].rotate(rotation);
            this->draw_tetromino(this->tetrominos[i].xpos, this->tetrominos[i].ypos, this->tetrominos[i]);
        } else {
            this->draw_tetromino(this->tetrominos[i].xpos, this->tetrominos[i].ypos, this->tetrominos[i]);
        }
    }
}
