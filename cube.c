#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

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
        print_face_row(cube, TOP, row);
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
        print_face_row(cube, BOTTOM, row);
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


//cube->sides[row_cycle[i]].cells[0][0] = 2;
void shift_row(Cube *cube, int row, RowDir dir){
    assert(row == 0 || row == 2); // middle row will never rotate in this solver

    static const FaceIndex rtl[4] = {LEFT, FRONT, RIGHT, BACK};
    static const FaceIndex ltr[4] = {RIGHT, FRONT, LEFT, BACK};
    const FaceIndex *row_cycle = (dir == LEFT_TO_RIGHT) ? ltr : rtl;

    int opposite_row = row == 0 ? 2 : 0;

    Face last_side_to_copy = cube->sides[BACK];

    for(int col = 0; col < 3; col++){
        cube->sides[BACK].cells[opposite_row][col] = cube->sides[row_cycle[0]].cells[row][col];
    }


    for(int i = 0; i < 2; i++){
        for(int col = 0; col < 3; col++){
            cube->sides[row_cycle[i]].cells[row][col] = cube->sides[row_cycle[i+1]].cells[row][col];
        }
    }
    
    for(int col = 0; col < 3; col++){
        cube->sides[row_cycle[2]].cells[row][col] = last_side_to_copy.cells[opposite_row][col];
    }

    //print_cube(cube);

}

void shift_col(Cube *cube, int col, ColDir dir){
    assert(col == 0 || col == 2); // middle row will never rotate in this solver

    static const FaceIndex faces[4] = {TOP, FRONT, BOTTOM, BACK};

    Face last_side_to_copy = cube->sides[TOP];
    

    for(int i = 0; i < 3; i++){
        for(int row = 0; row < 3; row++){
            cube->sides[faces[i]].cells[row][col] = cube->sides[faces[i + 1]].cells[row][col];
        }
    }

    for(int row = 0; row < 3; row++){
        cube->sides[BACK].cells[row][col] = last_side_to_copy.cells[row][col];
    }

}

void rotate_face(Cube *cube, FaceIndex face, bool clockwise){
    // Color last_to_copy_corner = cube->sides[face].cells[0][0];
    // Color last_to_copy_side = cube->sides[face].cells[0][1];
    
    // // NOT clockwise side = (0,1) <- (1,0) <- (2,1) <- (1,2) <- last
    // // NOT clockwise corner = (0,0) <- (2,0) <- (2,2) <- (0,2) <- last

    // clockwise side = (0,1) <- (1,2) <- (2,1) <- (1,0) <- last
    // clockwise corner = (0,0) <- (0,2) <- (2,2) <- (0,2) <- last
    // for(int i = 0; i < 3; i++){
        
    // }
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