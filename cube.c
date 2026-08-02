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


void universal_shift(Color *lines[4][3], ShiftDirection dir){
    Color temp[3];
    int line_i, line_finish, move_by;

    // pick where we start, where we stop and which way we walk the lines
    // left shift goes 0 -> 3, right shift goes the other way
    if(dir == LEFT_SHIFT){
        line_i = 0;
        line_finish = 3;
        move_by = 1;
    }
    else{
        line_i = 3;
        line_finish = 0;
        move_by = -1;
    }

    // save the first line, the loop overwrites it first so we put it back at the end
    for(int i = 0; i < 3; i++){
        temp[i] = *lines[line_i][i];
    }

    // every line takes the values from the next one in the walk direction
    while(line_i != line_finish){
        for(int cell_i = 0; cell_i < 3; cell_i ++){
            *lines[line_i][cell_i] = *lines[line_i + move_by][cell_i];
        }
        line_i += move_by;
    }

    // last line gets the saved one so nothing is lost
    for(int i = 0; i < 3; i++){
        *lines[line_finish][i] = temp[i];
    }
}


void shift_col(Cube *cube, int col, ColDir dir){
    assert(col == 0 || col == 2); // middle column never rotates in this solver

    Color *lines[4][3];
    FaceIndex faces[4] = {TOP, FRONT, BOTTOM, BACK};

    for(int face_i = 0; face_i < 4; face_i++){
        for(int cell_i = 0; cell_i < 3; cell_i++){
            lines[face_i][cell_i] = &(cube->sides[faces[face_i]].cells[cell_i][col]);
        }
    }

    // !dir turns ColDir into ShiftDirection: top_to_bottom -> right shift, bottom_to_top -> left shift
    universal_shift(lines, !dir);
}

//cube->sides[row_cycle[i]].cells[0][0] = 2;
void shift_row(Cube *cube, int row, RowDir dir){
    assert(row == 0 || row == 2); // middle row never rotates in this solver

    Color *lines[4][3];
    FaceIndex faces[4] = {LEFT, FRONT, RIGHT, BACK};

    int opposite_row = row == 2 ? 0 : 2; 

    for(int face_i = 0; face_i < 3; face_i++){
        for(int cell_i = 0; cell_i < 3; cell_i++){
            lines[face_i][cell_i] = &(cube->sides[faces[face_i]].cells[row][cell_i]);
        }
    }

    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[3][cell_i] = &(cube->sides[faces[3]].cells[opposite_row][cell_i]);
    }

    universal_shift(lines, !dir);
}

// REPAIR THIS
void shift_cir(Cube *cube, int circle, bool clockwise){
    assert(circle == 0 || circle == 2); // middle circle never rotates in this solver

    Color *lines[4][3];
    FaceIndex faces[4] = {TOP, RIGHT, BOTTOM, LEFT};
    
    int top_i = circle == 2 ? 0 : 2;
    int right_i = circle;
    int bottom_i = circle; 
    int left_i = circle == 2 ? 0 : 2;
    
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[0][cell_i] = &(cube->sides[faces[0]].cells[top_i][cell_i]);
    }

    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[1][cell_i] = &(cube->sides[faces[1]].cells[bottom_i][cell_i]);
    }

    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[2][cell_i] = &(cube->sides[faces[2]].cells[cell_i][right_i]);
    }

    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[3][cell_i] = &(cube->sides[faces[3]].cells[cell_i][left_i]);
    }
    
    universal_shift(lines, LEFT_SHIFT);


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