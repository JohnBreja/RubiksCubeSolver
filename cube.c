#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "cube.h"

void print_face_row(Cube *cube, FaceIndex face, int row);

Cube *init_cube(){
    Cube *cube = malloc(sizeof(Cube));
    
    if (cube == NULL){
        return NULL;
    }

    Color colors[6] = {WHITE, BLUE, YELLOW, ORANGE, RED, GREEN};
    for(int color_i = 0; color_i < 6; color_i++){
        Face *face = &cube->sides[color_i];
        for(int row = 0; row < 3; row++){
            for (int col = 0; col < 3; col++){
                face->cells[row][col] = colors[color_i];
            }
        }
    }
    return cube;
}

void free_cube(Cube *cube){
    free(cube);
}

void print_cube(Cube *cube){
    printf("\n");
    
    // First row
    for(int row = 0; row <3; row++){
        printf("       ");
        print_face_row(cube, UP, row);
        printf("\n");
    }
    printf("\n");

    // Second row
    for(int row = 0; row <3; row++){
        print_face_row(cube, LEFT, row);
        printf(" ");
        print_face_row(cube, FRONT, row);
        printf(" ");
        print_face_row(cube, RIGHT, row);
        printf("\n");
    }
    printf("\n");

    // Third row
    for(int row = 0; row <3; row++){
        printf("       ");
        print_face_row(cube, DOWN, row);
        printf("\n");
    }
    printf("\n");

    // Fourth row
    for(int row = 0; row <3; row++){
        printf("       ");
        print_face_row(cube, BACK, row);
        printf("\n");
    }
    printf("\n");

}

void print_face_row(Cube *cube, FaceIndex face, int row){
    char letters[6] = {'W','B','R','Y','G','O'};
    for(int col = 0; col < 3; col++){
        printf("%c ", letters[cube->sides[face].cells[row][col]]);
    }
}

Cube *copy_cube(Cube *cube){
    if (cube == NULL){
        return NULL;
    }

    Cube *new_cube = malloc(sizeof(Cube));
    if(new_cube == NULL){
        return NULL;
    }
    *new_cube = *cube;
    return new_cube;
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