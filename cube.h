

typedef enum {
    WHITE,
    BLUE,
    RED,
    YELLOW,
    GREEN,
    ORANGE
} Color;

typedef enum {
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    UP,
    DOWN
} FaceIndex;

typedef struct {
    Color cells[3][3];
} Face;

typedef struct {
    Face sides[FRONT, BACK, RIGHT, LEFT, UP, DOWN];
} Cube;
