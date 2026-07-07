#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    printf("Hello");
    Cube *cube = init_cube();   // vytvor kocku (malloc vnútri)
    print_cube(cube);           // vypíš ju ako kríž
    free_cube(cube);            // uvoľni pamäť
    return 0;
}
