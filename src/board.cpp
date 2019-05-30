#include "board.hpp"


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

int Board::store_tetromino(int xcoord, int ycoord, char shape_type, int n_of_90_degree_rotation) {
    if (!this->is_free_block(xcoord, ycoord, -1)) {
        std::cout << "(" << ycoord << ", " << xcoord << ") is not a free position" << std::endl;
        //exit(1);
    }

    // creating and rotating tetromino object
    Tetromino t = Tetromino(shape_type, xcoord, ycoord, this->get_new_tetromino_id());
    t.rotate(n_of_90_degree_rotation);

    this->draw_tetromino(xcoord, ycoord, t);
    this->tetrominos.push_back(t);
    return t.id;
}

void Board::draw_tetromino(int xcoord, int ycoord, Tetromino &t) {
    Pair pads = t.get_paddings();

    int xpad = pads[0],
        ypad = pads[1];

    for (int i = 0; i < 5; i++) {  // place tetromino to the board
        for (int j = 0; j < 5; j++) {
            if (t.pixels[i][j] == 1) {
                int newx = xcoord + j - xpad,
                    newy = ycoord + i - ypad;

                bool is_free_b = is_free_b = this->is_free_block(newx, newy, t.id);

                if (is_free_b) {
                    this->board[newy][newx] = 1;
                }

            }
        }
    }

}

bool Board::is_free_block(int xcoord, int ycoord, int tetromino_id) {
    if (this->board[ycoord][xcoord] == 1 ||
        xcoord >= BOARD_WIDTH ||
        ycoord >= BOARD_HEIGHT) {

        if (this->current_tetromino_id != tetromino_id && this->board[ycoord][xcoord] == 0) {
            return true;
        }

        this->restore_board();  // abord changes on the board
        this->throw_new_tetromino();  // throw a new playable tetromino

        return false;
    }
    return true;
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

void Board::throw_new_tetromino() {
    // choose a random shape with random rotation
    srand(time(NULL));
    int id = this->store_tetromino(0, 0, SHAPE_TYPES[rand() % 5], rand() % 4);
    this->current_tetromino_id = id;
}

void Board::remove_last_line_if_possible() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (this->board[BOARD_HEIGHT - 1][i] == 0) {
            return;
        }
    }

    // remove last line
    this->save_board();
    this->clean_up();

    for (int i = 1; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->board[i][j] = this->prev_board[i - 1][j];
        }
    }

    try {
        this->tetrominos[this->current_tetromino_id].ypos++;
    }
    catch (const std::out_of_range &oor) {}
}

bool Board::is_won() {
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
