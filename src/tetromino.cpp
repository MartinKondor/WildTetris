#include <iostream>
#include "tetromino.hpp"


/**
 * An Inplace function to rotate a NxN matrix 
 * by 90 degrees in anti-clockwise direction 
 * 
 * Worst case: O(n^2)
 * compared to the "reverse_rows(transpose(Array))"
 * method (O(n^2 + n)), it's faster
 */
const void rotate_matrix(int mat[5][5]) {
    for (int x = 0; x < 5 / 2; x++) {
        for (int y = x; y < 5 - 1 - x; y++) {
            int temp = mat[x][y];
  
            // move values from right to top 
            mat[x][y] = mat[y][5 - 1 - x]; 
  
            // move values from bottom to right 
            mat[y][5 - 1 - x] = mat[5 - 1 - x][5 - 1 - y]; 
  
            // move values from left to bottom 
            mat[5 - 1 - x][5 - 1 - y] = mat[5 - 1 - y][x]; 
  
            // assign temp to left 
            mat[5 - 1 - y][x] = temp; 
        } 
    } 
} 



// Constructor
Tetromino::Tetromino(char shape_type)
: pixels {{0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0}}
{
    this->rotation = 0;
    this->shape_type = shape_type;

    switch (shape_type) {
        case 'Z':
            pixels[1][3] = 1;
            pixels[2][3] = 1;
            pixels[2][2] = 1;
            pixels[3][2] = 1;
            break;
        case 'T':
            pixels[1][2] = 1;
            pixels[2][1] = 1;
            pixels[2][2] = 1;
            pixels[2][3] = 1;
            break;
        case 'I':
            pixels[1][2] = 1;
            pixels[2][2] = 1;
            pixels[3][2] = 1;
            pixels[4][2] = 1;
            break;
        case 'L':
            pixels[1][2] = 1;
            pixels[2][2] = 1;
            pixels[3][2] = 1;
            pixels[3][3] = 1;
            break;
        case 'S':
            pixels[2][2] = 1;
            pixels[2][3] = 1;
            pixels[3][2] = 1;
            pixels[3][3] = 1;
            break;
    
        default:
            std::cout << "'" << shape_type << "' shape cannot be inicialized" << std::endl;
            exit(1);
            break;
    }
}

const void Tetromino::rotate(int clockwise_n_of_90) {
    if (clockwise_n_of_90 >= 0 && clockwise_n_of_90 <= 4) {
        for (int i = 0; i < clockwise_n_of_90; i++) {
            rotate_matrix(this->pixels);
        }
    } else {
        std::cout << "cannot rotate matrix by " << clockwise_n_of_90*90 << " degree" << std::endl;
        exit(1);
    }
}

const void Tetromino::print() {
    std::cout << "Shape: " << this->shape_type << std::endl;
    std::cout << "Rotation: " << this->rotation*90 << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << this->pixels[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}
