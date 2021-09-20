#include <gb/gb.h>
#include <stdio.h>

#define FRAME_INCREMENT 15

void main()
{
    int frameCount = 1;
    while(1)
    {
        if (frameCount % FRAME_INCREMENT == 0)
        {
            printf("Animate\n", frameCount);
            frameCount = 0;
        }
        frameCount++;
        wait_vbl_done();
    }
}
