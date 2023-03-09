#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

typedef enum Error {
    ERR_NONE,
    ERR_ALLOC,
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
