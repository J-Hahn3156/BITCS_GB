// gdbk include
#include <gb/gb.h>
#include <stdio.h>
#include "shelf.c"
#include "bkg.c"
#include "pots.c"
#include "meta_sprite.c"
#define POTS_COUNT 9 
#define SPRITE_SIZE 16

movingPot potting[POTS_COUNT];

player p;

void updatePot(UINT8 potID, UINT8 x, UINT8 y){
    UINT8 spriteID = potID * 4;

    move_sprite(spriteID, x, y);
    move_sprite(spriteID + 1 , x + 8, y);
    move_sprite(spriteID + 2, x, y + 8);
    move_sprite(spriteID + 3, x + 8, y + 8);
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

    set_sprite_tile(spriteID, 0);
    set_sprite_tile(spriteID + 1, 1);
    set_sprite_tile(spriteID + 2, 2);
    set_sprite_tile(spriteID + 3, 3);

    potting[potID].sprite.ID[0] = 0;
    potting[potID].sprite.ID[1] = 1;
    potting[potID].sprite.ID[2] = 2;
    potting[potID].sprite.ID[3] = 3;

    

    updatePot(potID, potting[potID].sprite.x, potting[potID].y);
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

    updatePlayer(&p, p.sprite.x, 118);
}

//setup sprites, widow, and background
void init(){
    UINT8 counter = 0;
    set_bkg_data(0, 3, shelf);
    set_bkg_tiles(0,0,20,18,bkg_map);

    set_sprite_data(0,8, spriteTile);
    
    
    while (counter < POTS_COUNT){
        
        UINT8 potX, potY;
        potY = counter/3;
        potX = counter% 3;
        setupPot(30 + potX * 50, 33 + potY * 16 ,counter);
        counter ++;
    }

    setupPlayer();


    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}

//main
void main(){
    init();
}
