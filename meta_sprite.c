#include <gb/gb.h>

enum potState
{
    INVISIBLE, 
    STANDING, 
    FALLING,
    BROKEN
};

typedef struct
{
    UINT8 ID[4];
    UINT8 x;
    UINT8 h;
    UINT8 w;
} metaSprite;

typedef struct
{
    metaSprite sprite;
    UBYTE placeholder;
} player;

typedef struct
{
    metaSprite sprite;
    UINT8 y;
    enum potState state;
} movingPot;

