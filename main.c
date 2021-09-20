#include <gb/gb.h>
#include <gb/types.h>
#include <stdio.h>

void main()
{
    BYTE frameCount = 0;
    while(1)
    {
        printf("HELLO WORLD %d\n", frameCount);
        frameCount++;
        wait_vbl_done();
    }
}
