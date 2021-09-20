#include <gb/gb.h>
#include <stdio.h>

#define FRAME_INCREMENT 15

void main()
{
    int frameCount = 0;
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
