#ifndef CASE_INCLUDED
#define CASE_INCLUDED

typedef struct _case {
    int x, y;
} Case;

typedef enum _direction {
    UP = 1, DOWN,
    LEFT, RIGHT
} Direction;

#endif