/*---------------------------------------------------------------

Game is the class which handles the graphics
and controls of the game.

---------------------------------------------------------------*/
#ifndef _GAME_
#define _GAME_

class Game {
    private:
    Board board;
    int rotation;
    int xmove;
    int ymove;
    
    public:
    Game();
    const void start();
    const char handle_keys();
    const void showinfo();
    const void show();
};

#endif
