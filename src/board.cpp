#include "board.hpp"


Board::Board() {
    this->tetrominos = {};
    this->tetromino_id = 0;
    this->current_tetromino_id = 0;
    this->score = 0;
    this->game_is_over = false;

    // filling the boards with 0s
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = 0;
            this->prev_board[i][j] = 0;
        }
    }

}

void Board::throw_new_tetromino() {
    srand(time(NULL));

    // choose a random shape with random rotation
    const char choosen_shape = SHAPE_TYPES[rand() % 5];
    const int choosen_rotation = rand() % 4;

    this->current_tetromino_id = this->store_tetromino(BOARD_WIDTH / 2 - 1, 0, choosen_shape, choosen_rotation);
}

int Board::store_tetromino(int xcoord, int ycoord, char shape_type, int rotation) {
    if (!this->is_free_block(xcoord, ycoord)) {
        // probably it's spawning on filled coordinates

        if (xcoord >= BOARD_WIDTH || ycoord >= BOARD_HEIGHT) {
            // it's a game over
            this->game_is_over = true;
            return -1;
        }

        // try to spawn somewhere else
        return this->store_tetromino(xcoord + 1, ycoord, shape_type, rotation);
    }

    // creating and rotating tetromino object
    Tetromino t = Tetromino(shape_type, xcoord, ycoord, this->get_new_tetromino_id());
    t.rotate(rotation);

    this->draw_tetromino(xcoord, ycoord, t);
    this->tetrominos.push_back(t);
    return t.id;
}

bool Board::is_free_block(int xcoord, int ycoord) {
    if (this->board[ycoord][xcoord] == 1 ||
        xcoord >= BOARD_WIDTH || ycoord >= BOARD_HEIGHT ||
        xcoord < 0 || ycoord < 0) {
        return false;
    }
    return true;
}

void Board::draw_tetromino(int xcoord, int ycoord, Tetromino &tetromino) {
    Pair pads = tetromino.get_paddings();

    int xpad = pads[0],
        ypad = pads[1];

    for (int i = 0; i < 5; i++) {  // place tetromino to the board
        for (int j = 0; j < 5; j++) {
            if (tetromino.pixels[i][j] == 1) {
                int newx = xcoord + j - xpad,
                    newy = ycoord + i - ypad;

                if (this->is_free_block(newx, newy)) {
                    this->board[newy][newx] = 1;
                } else {
                    // allow the non current box to go beyond height
                    // this occurs when we remove the last line
                    if (this->current_tetromino_id != tetromino.id) {
                        continue;
                    }

                    // abord changes on the board, this way making the current_tetromino
                    // stop on the bottom or on the top of an other box
                    this->restore_board();

                    // throw a new playable tetromino
                    this->throw_new_tetromino();
                }

            }
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

void Board::save_board() {
    this->prev_tetrominos = this->tetrominos;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->prev_board[i][j] = this->board[i][j];
        }
    }
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
            if (this->board[i][j] == 1) {
                rlutil::setBackgroundColor(8);
            } else {
                rlutil::setBackgroundColor(15);
            }
            std::cout << "  ";
            rlutil::resetColor();
        }
        std::cout << std::endl;
    }
    rlutil::resetColor();
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

    // draw the non current tetrominos first
    for (int i = 0; i < this->tetrominos.size(); i++) {
        if (this->current_tetromino_id != this->tetrominos[i].id) {
            this->draw_tetromino(this->tetrominos[i].xpos, this->tetrominos[i].ypos, this->tetrominos[i]);
        }
    }
    
    try {
        Tetromino &current = this->tetrominos.at(this->current_tetromino_id);
        current.xpos += xmove;
        current.ypos += ymove;
        current.rotate(rotation);
        this->draw_tetromino(current.xpos, current.ypos, current);
    }
    catch (const std::out_of_range &oor) {}
}

void Board::remove_last_line_if_possible() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (this->board[BOARD_HEIGHT - 1][i] == 0) {
            return;
        }
    }

    this->save_board();
    this->clean_up();

    // remove last line
    for (int i = 1; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = this->prev_board[i - 1][j];
        }
    }

    this->score += 1;

    // remove a line after the current tetromino too
    try {
        this->tetrominos[this->current_tetromino_id].ypos++;
    }
    catch (const std::out_of_range &oor) {}
}

bool Board::is_won() {

    if (this->game_is_over) {
        return false;
    }

    // collect the filled columns
    bool is_there_a_filled_column = false;

    for (int j = 0; j < BOARD_WIDTH; j++) {
        int sum = 0;
        
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            sum += this->board[i][j];
        }

        if (sum == BOARD_HEIGHT) {
            is_there_a_filled_column = true;
            break;
        } 
    }

    if (is_there_a_filled_column) {
        return false;
    }

    return true;
}
