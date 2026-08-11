#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

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
    // all six moves in an array so we can pick one by index
    MoveFn moves[6] = { move_TOP, move_BOTTOM, move_LEFT,
                    move_RIGHT, move_FRONT, move_BACK };
    int function_i, clockwise;
    MoveFn move_fun;

    // 100 random moves to scramble the cube
    for (int i = 0; i < 100; i ++){
        function_i = rand() % 6;        // pick a random move 0..5
        move_fun = moves[function_i];   // pull it out of the array
        clockwise = i & 1;              // last bit of i alternates 0,1,0,1 -> flip direction each move
        move_fun(cube, (bool) clockwise);
    }
}

bool is_solved(Cube *cube){
    static Cube solved;
    static bool ready = false;

    if(!ready){
        FaceIndex faces[6] = {BOTTOM, FRONT, TOP, LEFT, RIGHT, BACK};
        Color colors[6] = {WHITE, BLUE, YELLOW, ORANGE, RED, GREEN};
        
        for(int face_i = 0; face_i < 6; face_i++){
            for (int row_i = 0; row_i < 3; row_i++)
            {
                for (int col_i = 0; col_i < 3; col_i++)
                {
                    solved.sides[faces[face_i]].cells[row_i][col_i] = colors[face_i];
                }
                
            }
            
        }

        ready = true;
    }
    
    return memcmp(cube, &solved, sizeof(Cube)) == 0;
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
    universal_shift(lines, dir);
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

    // BACK is filled reversed so the seam lines up at the corner,
    // same trick as in shift_cir. real cube confirms it.
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[3][cell_i] = &(cube->sides[faces[3]].cells[opposite_row][2 - cell_i]);
    }

    universal_shift(lines, !dir);
}

// REPAIR THIS
void shift_cir(Cube *cube, int circle, bool clockwise){
    assert(circle == 0 || circle == 2); // middle circle never rotates in this solver

    Color *lines[4][3];
    // walk order around the circle: TOP -> RIGHT -> BOTTOM -> LEFT
    FaceIndex faces[4] = {TOP, RIGHT, BOTTOM, LEFT};

    // which row/col of each face touches this slice
    // circle 0 = front slice, circle 2 = back slice
    int top_i = circle == 2 ? 0 : 2;    // top face uses a row
    int right_i = circle;               // right face uses a col
    int bottom_i = circle;              // bottom face uses a row
    int left_i = circle == 2 ? 0 : 2;   // left face uses a col
    
    // top and bottom are rows so cell_i walks along the columns
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[0][cell_i] = &(cube->sides[faces[0]].cells[top_i][cell_i]);
    }

    // bottom is filled reversed so it lines up at the corner with the others
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[2][cell_i] = &(cube->sides[faces[2]].cells[bottom_i][2 - cell_i]);
    }

    // right and left are cols so cell_i walks along the rows
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[1][cell_i] = &(cube->sides[faces[1]].cells[cell_i][right_i]);
    }

    // left is filled reversed too, same corner reason as bottom
    for(int cell_i = 0; cell_i < 3; cell_i++){
        lines[3][cell_i] = &(cube->sides[faces[3]].cells[2 - cell_i][left_i]);
    }

    // NOTE: rows and cols meet at the corners so some lines probably need the
    // reversed fill order, universal_shift only copies index to index. Test it.
    universal_shift(lines, (ShiftDirection) clockwise);


}

void print(int num){
    printf("%d\n", num);
}

void rotate_face(Cube *cube, FaceIndex face, bool clockwise){
    Color temp_corner = cube->sides[face].cells[0][0];
    Color temp_side = cube->sides[face].cells[0][1];

    int temp_ax_corner, temp_ax_side;
    
    int x_side = 0;
    int y_side = 1;
    int x_corner = 0;
    int y_corner = 0;

    // yeah I know this looks scary but it works, tested it
    // this is just the rotate-around-origin formula from math class.
    // source cell of (x,y) is (x_sign*y + x_plus, y_sign*x + y_plus).
    // the sign flips the axis and the plus is the N-1 shift so indexes never go negative.
    // clockwise and counter just swap which axis gets flipped.
    int x_plus, y_plus, x_sign, y_sign;

    if(clockwise){
        x_plus = 2;
        x_sign = -1;
        y_plus = 0;
        y_sign = 1;
    }
    else{
        x_plus = 0;
        x_sign = 1;
        y_plus = 2;
        y_sign = -1;
    }
    
    for(int i = 0; i < 3; i++){
        cube->sides[face].cells[x_side][y_side] = cube->sides[face].cells[x_sign * y_side + x_plus][y_sign * x_side + y_plus];
        temp_ax_side = x_side;
        x_side = x_sign * y_side + x_plus;
        y_side = y_sign * temp_ax_side + y_plus;

        cube->sides[face].cells[x_corner][y_corner] = cube->sides[face].cells[x_sign * y_corner + x_plus][y_sign * x_corner + y_plus];
        temp_ax_corner = x_corner;
        x_corner = x_sign * y_corner + x_plus;
        y_corner = y_sign * temp_ax_corner + y_plus;
    }
    cube->sides[face].cells[x_side][y_side] = temp_side;
    cube->sides[face].cells[x_corner][y_corner] = temp_corner;

}

void move_TOP(Cube *cube, bool clockwise){
    rotate_face(cube, TOP, clockwise);
    shift_row(cube, 0, clockwise);
}

void move_BOTTOM(Cube *cube, bool clockwise){
    // BOTTOM is opposite TOP, so its local indexing flips rotate_face's
    // "clockwise" vs the outside view. invert to match a real cube.
    rotate_face(cube, BOTTOM, clockwise);
    shift_row(cube, 2, !clockwise);
}

void move_LEFT(Cube *cube, bool clockwise){
    rotate_face(cube, LEFT, clockwise);
    shift_col(cube, 0, clockwise);
}

void move_RIGHT(Cube *cube, bool clockwise){
    // RIGHT's local indexing makes rotate_face's "clockwise" come out flipped
    // vs the outside view, so we invert here to match a real cube (like move_TOP)
    rotate_face(cube, RIGHT, clockwise);
    shift_col(cube, 2, !clockwise);
}

void move_FRONT(Cube *cube, bool clockwise){
    rotate_face(cube, FRONT, clockwise);
    shift_cir(cube, 0, clockwise);
}

void move_BACK(Cube *cube, bool clockwise){
    rotate_face(cube, BACK, clockwise);
    shift_cir(cube, 2, !clockwise);
}