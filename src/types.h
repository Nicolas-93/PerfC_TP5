#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

typedef enum Error {
    ERR_NONE,
    ERR_ALLOC,
    ERR_EXIT,
} Error;

typedef struct _case {
    int x, y;
} Case;

typedef enum _direction {
            UP = 1,
    LEFT,            RIGHT,
            DOWN,
} Direction;

#endif
