#include "board.hpp"

using std::cout;
using std::endl;

Board::Board() {
    this->tetrominos = {};
    this->tetromino_id = 0;
    this->current_tetromino_id = 0;

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = 0;
            this->prev_board[i][j] = 0;
        }
    }
}

void Board::save_board() {
    this->prev_tetrominos = this->tetrominos;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->prev_board[i][j] = this->board[i][j];
        }
    }
}

void Board::restore_board() {
    this->tetrominos = this->prev_tetrominos;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = this->prev_board[i][j];
        }
    }
}

int Board::store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation) throw (const char*) {
    if (!this->is_free_block(xcoord, ycoord)) {
        std::cout << "(" << ycoord << ", " << xcoord << ") is not a free position" << std::endl;
        exit(1);
    }

    // creating and rotating tetromino object
    Tetromino t = Tetromino(shape_type, xcoord, ycoord, this->get_new_tetromino_id());
    t.rotate(n_of_90_degree_rotation);

    try {
        this->draw_tetromino(xcoord, ycoord, t);
    }
    catch (const char* err) {
        throw err;
    }

    this->tetrominos.push_back(t);
    return t.id;
}

void Board::draw_tetromino(int xcoord, int ycoord, Tetromino &t) throw (const char*) {
    Pair pads = t.get_paddings();

    int xpad = pads.pair[0],
        ypad = pads.pair[1];

    for (int i = 0; i < 5; i++) {  // place tetromino to the board
        for (int j = 0; j < 5; j++) {
            if (t.pixels[i][j] == 1) {
                int newx = xcoord + j - xpad,
                    newy = ycoord + i - ypad;

                bool is_free_b = false;
                try {
                    is_free_b = this->is_free_block(newx, newy);
                }
                catch (const char* err) {
                    throw err;
                }

                if (is_free_b) {
                    this->board[newy][newx] = 1;
                }
            }
        }
    }
}

bool Board::is_free_block(int xcoord, int ycoord) throw (const char*) {
    if (xcoord >= BOARD_WIDTH) {
        throw "out of width";
    }
    if (ycoord >= BOARD_HEIGHT) {
        throw "out of height";
    }

    // collusion detection
    try {
        Tetromino current_tetromino = this->tetrominos.at(this->current_tetromino_id);
        cout << endl;

        // find the coordinates to "current_tetromino"'s 1s and check if they are free or not
        // TODO
    }
    catch (const std::out_of_range& oor) {}

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
            std::cout << this->board[i][j] << "  ";
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
    this->save_board();
    this->clean_up();

    for (int i = 0; i < this->tetrominos.size(); i++) {
        if (this->current_tetromino_id == this->tetrominos[i].id) {
            this->tetrominos[i].xpos += xmove;
            this->tetrominos[i].ypos += ymove;
            this->tetrominos[i].rotate(rotation);
            this->draw_tetromino(this->tetrominos[i].xpos, this->tetrominos[i].ypos, this->tetrominos[i]);
        } else {
            this->draw_tetromino(this->tetrominos[i].xpos, this->tetrominos[i].ypos, this->tetrominos[i]);
        }
    }
}

void Board::throw_new_tetromino() {
    // choose a random shape with random rotation
    srand(time(NULL));
    int id = this->store_tetromino(1, 0, SHAPE_TYPES[rand() % 5], rand() % 4);

    this->current_tetromino_id = id;
}
