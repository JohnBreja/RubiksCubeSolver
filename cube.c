#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "cube.h"

Cube *init_cube(){
    Cube *cube = malloc(sizeof(Cube));
    // TODO set collors
    return cube;
}

void free_cube(Cube *cube){
    free(cube);
}

void print_cube(Cube *cube){
    // TODO
}

Cube *copy_cube(Cube *cube){
    // TODO
}

void randomise_cube(Cube *cube){
    // TODO
}

bool is_solved(Cube *cube){
    // TODO
}

int count_moves(Cube *cube){
    // TOOD
}

void shift_row(Cube *cube, int row, RowDir dir){
    // TODO
}

void shift_col(Cube *cube, int col, ColDir dir){
    // TODO
}

void rotate_face(Cube *cube, FaceIndex face, bool clockwise){
    // TODO
}

void move_UP(Cube *cube, bool clockwise){
    // TODO
}

void move_DOWN(Cube *cube, bool clockwise){
    // TODO
}

void move_LEFT(Cube *cube, bool clockwise){
    // TODO
}

void move_RIGHT(Cube *cube, bool clockwise){
    // TOOD
}

void move_FRONT(Cube *cube, bool clockwise){
    // TOOD
}

void move_BACK(Cube *cube, bool clockwise){
    // TODO
}