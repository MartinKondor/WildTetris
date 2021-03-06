/*---------------------------------------------------------------

Tetromino object which may represent the following
shapes or "tetromino"s:
    * L shape
    * Z shape
    * T shape
    * S for square
    * I shape

Also the object itself contains the rotation of the Tetromino.

---------------------------------------------------------------*/
#ifndef _TETROMINO_
#define _TETROMINO_

const char SHAPE_TYPES[5] = {'L', 'Z', 'T', 'S', 'I'};

class Tetromino {
    public:

    /**
    * Container for the pixels of an element
    */
    int pixels[5][5];

    /**
     * Containing the number of 90 degree anti-clockwise rotations
     * 1 = 90 degree
     * ...
     * 4 = 360 degree
     */
    int rotation;
    char shape_type;
    int xpos;
    int ypos;
    int id;
    int color;

    Tetromino(char shape_type, int xpos, int ypos, int id);

    /**
     * Rotate the pixels array to the given degree
     */
    const void rotate(int clockwise_n_of_90);
    const void print();
    Pair get_paddings();
};

#endif
