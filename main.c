// gdbk include
#include <gb/gb.h>
#include <stdio.h>

// project include
#include "types.h"

#define FRAME_INCREMENT 15

void init()
{
    
}

void main()
{
    init();
    int frameCount = 0;
    Player player;
    
    while(1)
    {
        // game logic
        if (frameCount % FRAME_INCREMENT == 0)
        {
            printf("anim on frame %d\n", frameCount);
        }
        
        // frame increment and timing
        frameCount++;
        if (frameCount >= 60)
        {
            frameCount = 0;
        }
        wait_vbl_done();
    }
}
