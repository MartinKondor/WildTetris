#include "game.hpp"

using std::cout;
using std::endl;

Game::Game() {
    this->board = Board();
    this->rotation = 0;
    this->xmove = 0;
    this->ymove = 1;
}

const void Game::show() {
    this->showinfo();
    this->board.print();
}

const void Game::start() {
    rlutil::saveDefaultColor();
    this->show();

    // throw the first tetromino
    this->board.throw_new_tetromino();
    char keypress = '-';
    bool in_pause = true;  // for first we wait for the start button

    while (true) {
        Sleep(50);

        if (in_pause) {
            keypress = this->handle_keys();
            if (keypress == 'S') {
                in_pause = false;
            }
            else if (keypress == 'E') {
                break;
            }
            continue;
        }

        keypress = this->handle_keys();
        if (keypress == 'E') {
            break;
        }
        else if (keypress == 'P') {
            in_pause = true;
        }

        // Clear the screen
        COORD position;
        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
        position.X = 0;
        position.Y = 0;
        SetConsoleCursorPosition(hout, position);
        
        this->board.update(this->rotation, this->xmove, this->ymove);
        this->board.remove_last_line_if_possible();
        this->show();

        // check win conditions
        if (!this->board.is_won()) {
            std::cout << "<<<<<<<<<<           >>>>>>>>>>" << std::endl;
            std::cout << "<<<<<<<<<< GAME OVER >>>>>>>>>>" << std::endl;
            std::cout << "<<<<<<<<<<           >>>>>>>>>>" << std::endl;
            Sleep(500);
            in_pause = true;
            continue;
        }

        // reset movements
        this->xmove = 0;
        this->ymove = 1;
        this->rotation = 0;
    }

    rlutil::resetColor();
}

const char Game::handle_keys() {
    if (GetKeyState('S') & 0x8000) {  // start key
        return 'S';
    }
    if (GetKeyState('P') & 0x8000) {  // pause key
        return 'P';
    }
    if (GetKeyState('E') & 0x8000) {  // exit key
        return 'E';
    }
    if (GetKeyState('R') & 0x8000) {  // rotation key
        this->rotation++;
    }
    if (GetKeyState(VK_DOWN) & 0x8000) {
        this->ymove++;
    }
    if (GetKeyState(VK_UP) & 0x8000) {
        this->ymove--;
    }
    if (GetKeyState(VK_LEFT) & 0x8000) {
        this->xmove--;
    }
    if (GetKeyState(VK_RIGHT) & 0x8000) {
        this->xmove++;
    }
    return '-';
}

const void Game::showinfo() {
    std::cout << std::endl;
    std::cout << "Control keys:" << std::endl;
    std::cout << "(S)\tStart" << std::endl;
    std::cout << "(P)\tPause" << std::endl;
    std::cout << "(R)\tRotate" << std::endl;
    std::cout << "(E)\tExit" << std::endl;
    std::cout << std::endl;
    std::cout << "Score: " << this->board.score << std::endl;
    std::cout << std::endl;
}
