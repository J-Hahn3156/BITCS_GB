// gdbk include
#include <gb/gb.h>
#include <stdio.h>
#include "shelf.c"
#include "bkg.c"
#include "pots.c"
#include "meta_sprite.c"
#define POTS_COUNT 9
#define SPRITE_SIZE 16
#define PLACEMENT 118
#define SPEED 2
#define TEMPFALL 5
#define XOUTOFBOUNDS 160
#define YOUTOFBOUNDS 160

movingPot potting[POTS_COUNT];
player p;

void pDelay(UINT8 time){
    UINT8 i;
    for (i = 0; i < time; i++){
        wait_vbl_done();
    }
}


void updatePot(movingPot* pot, UINT8 potID){
    UINT8 spriteID = potID * 4;
    
/*
    move_sprite(pot -> sprite.ID[0], pot->sprite.x, pot->y);
    move_sprite(pot -> sprite.ID[1], pot->sprite.x + 8, pot->y);
    move_sprite(pot -> sprite.ID[2], pot->sprite.x, pot->y + 8);
    move_sprite(pot -> sprite.ID[3], pot->sprite.x + 8, pot->y + 8);
*/
    switch (pot->state)
    {
        case INVISIBLE:
            move_sprite(pot -> sprite.ID[0], XOUTOFBOUNDS, YOUTOFBOUNDS);
            move_sprite(pot -> sprite.ID[1], XOUTOFBOUNDS, YOUTOFBOUNDS);
            move_sprite(pot -> sprite.ID[2], XOUTOFBOUNDS, YOUTOFBOUNDS);
            move_sprite(pot -> sprite.ID[3], XOUTOFBOUNDS, YOUTOFBOUNDS);
            if(pot->frameCount >= 200){
                pot->state = STANDING;
            }
            break;
        case STANDING:
            move_sprite(pot -> sprite.ID[0], pot->sprite.x, pot->y);
            move_sprite(pot -> sprite.ID[1], pot->sprite.x + 8, pot->y);
            move_sprite(pot -> sprite.ID[2], pot->sprite.x, pot->y + 8);
            move_sprite(pot -> sprite.ID[3], pot->sprite.x + 8, pot->y + 8);
            break;
        case FALLING:
            pot->y += 2;
            move_sprite(pot -> sprite.ID[0], pot->sprite.x, pot->y);
            move_sprite(pot -> sprite.ID[1], pot->sprite.x + 8, pot->y);
            move_sprite(pot -> sprite.ID[2], pot->sprite.x, pot->y + 8);
            move_sprite(pot -> sprite.ID[3], pot->sprite.x + 8, pot->y + 8);

            if(pot->y >= 120){
                pot->state = BROKEN;
                pot->frameCount = 0;
            }

            break;
        case BROKEN:
            if(pot->frameCount >= 200){
                pot->state = INVISIBLE;
                pot->frameCount = 0;
            }
            break;
    }

}

void updatePlayer(player* p, UINT8 x, UINT8 y){
    move_sprite(p -> sprite.ID[0], x, y);
    move_sprite(p -> sprite.ID[1], x + 8, y);
    move_sprite(p -> sprite.ID[2], x, y + 8);
    move_sprite(p -> sprite.ID[3], x + 8, y + 8);
}

void setupPot(UINT8 x, UINT8 y, UINT8 potID){


    UINT8 spriteID = potID * 4;

    //struct movingPot pot = ms -> data;
    potting[potID].sprite.x = x;
    potting[potID].y = y;
    potting[potID].sprite.w = SPRITE_SIZE;
    potting[potID].sprite.h = SPRITE_SIZE;
    potting[potID].state = STANDING;
    potting[potID].frameCount = 0;

    set_sprite_tile(spriteID, 0);
    set_sprite_tile(spriteID + 1, 1);
    set_sprite_tile(spriteID + 2, 2);
    set_sprite_tile(spriteID + 3, 3);

    potting[potID].sprite.ID[0] = spriteID;
    potting[potID].sprite.ID[1] = spriteID + 1;
    potting[potID].sprite.ID[2] = spriteID + 2;
    potting[potID].sprite.ID[3] = spriteID + 3;
}

void setupPlayer(){

    p.sprite.x = 80;
    p.sprite.w = SPRITE_SIZE;
    p.sprite.h = SPRITE_SIZE;

    set_sprite_tile(36, 4);
    set_sprite_tile(37, 5);
    set_sprite_tile(38, 6);
    set_sprite_tile(39, 7);

    p.sprite.ID[0] = 36;
    p.sprite.ID[1] = 37;
    p.sprite.ID[2] = 38;
    p.sprite.ID[3] = 39;

    updatePlayer(&p, p.sprite.x, PLACEMENT);
}

//setup sprites, widow, and background
void init(){
    UINT8 counter = 0;
    set_bkg_data(0, 3, shelf);
    set_bkg_tiles(0,0,20,18,bkg_map);
    set_sprite_data(0,8, spriteTile);
    
    for (counter = 0; counter < POTS_COUNT; counter++)
    {
        UINT8 potX, potY;
        potY = counter/3;
        potX = counter% 3;
        setupPot(30 + potX * 50, 33 + potY * 16 ,counter);
    }

    setupPlayer();


    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}

//main
void main(){
    
    init();

    while(1){
        UINT8 x;

        for(x = 0; x < POTS_COUNT; x++){
            updatePot(&potting[x], x);
            if(potting[x].state == STANDING && potting[x].frameCount == 8){
                potting[x].frameCount = 0;
                if(potting[x].state == STANDING && joypad() & J_A){
                potting[TEMPFALL].state = FALLING;
            }
                
            }
            potting[x].frameCount++;
        }

        if((joypad() & J_LEFT) && (p.sprite.x != 8)){
            p.sprite.x -= 2;
        }
        if((joypad() & J_RIGHT) && (p.sprite.x != 152)){
            p.sprite.x += 2;
        }
        updatePlayer(&p, p.sprite.x, PLACEMENT);

        pDelay(1);
    }
}
