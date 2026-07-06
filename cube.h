
// Structure of Rubic's Cube (later RB)
typedef enum {
    WHITE,
    BLUE,
    RED,
    YELLOW,
    GREEN,
    ORANGE
} Color;

typedef enum {
    FRONT = 0,
    BACK = 1,
    RIGHT = 2,
    LEFT = 3,
    UP = 4,
    DOWN = 5
} FaceIndex;

typedef enum { LEFT_TO_RIGHT, RIGHT_TO_LEFT } RowDir;
typedef enum { TOP_TO_BOTTOM, BOTTOM_TO_TOP } ColDir;

typedef struct {
    Color cells[3][3];
} Face;

typedef struct {
    Face sides[6];
} Cube;


// ----- Main function for RB -----

Cube *init_cube();
void free_cube(Cube *cube);
void print_cube(Cube *cube);
Cube *copy_cube(Cube *cube);

void randomise_cube(Cube *cube);

bool is_solved(Cube *cube);
int count_moves(Cube *cube);

// ----- Solving functions -----

// Solving is split into two layers:
// Low-level (rotate_face_grid, shift_row, shift_col) handle raw grid manipulation

// High-level moves (move_U, move_R, ...) call low-level functions to represent
// actual cube moves.

// Low level

void shift_row(Cube *cube, int row, RowDir dir);
void shift_col(Cube *cube, int col, ColDir dir);
void rotate_face(Cube *cube, FaceIndex face, bool clockwise);

// High level

void move_UP(Cube *cube, bool clockwise);
void move_DOWN(Cube *cube, bool clockwise);
void move_LEFT(Cube *cube, bool clockwise);
void move_RIGHT(Cube *cube, bool clockwise);
void move_FRONT(Cube *cube, bool clockwise);
void move_BACK(Cube *cube, bool clockwise);