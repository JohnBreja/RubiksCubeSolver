#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {

    // shift row test
    Cube *cube = init_cube();
    print_cube(cube);
    printf("--------------------------\n");

    // shift_col(cube, 2, BOTTOM_TO_TOP);
    // shift_col(cube, 0, TOP_TO_BOTTOM);


    shift_row(cube, 0, LEFT_TO_RIGHT);
    shift_row(cube, 2, LEFT_TO_RIGHT);
    print_cube(cube);
    printf("--------------------------\n");

    // shift_cir(cube, 0, true);
    // shift_cir(cube, 2, false);

    rotate_face(cube, FRONT, false);

    print_cube(cube);
    free_cube(cube);
    return 0;
}



/*
    Cube *cube = init_cube();
    print_cube(cube);
    printf("--------------------------");
    shift_row(cube, 0, LEFT_TO_RIGHT);
    shift_row(cube, 2, RIGHT_TO_LEFT);
    print_cube(cube);

    shift_row(cube, 0, RIGHT_TO_LEFT);
    shift_row(cube, 2, LEFT_TO_RIGHT);


*/



