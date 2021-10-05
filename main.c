// gdbk include
#include <gb/gb.h>
#include <stdio.h>
#include "shelf.c"
#include "bkg.c"
#include "pots.c"
#include "meta_sprite.c"

movingPot potting[8];
UINT8 size = 16;

void spriteMovment(metaSprite* sp, UINT8 x, UINT8 y){
    move_sprite(sp->ID[0], x, y);
    move_sprite(sp->ID[1], x + 8, y);
    move_sprite(sp->ID[2], x, y + 8);
    move_sprite(sp->ID[3], x + 8, y + 8);
}

/*
void updatePot(metaSprite* pot){

}

void updatePlayer(metaSprite* player){

}
*/
void setupPot(UINT8 x, UINT8 y, UINT8 potID){
    
    UINT8 spriteID = potID >> 2;
    //struct movingPot pot = ms -> data;
    potting[potID].sprite.x = x;
    potting[potID].y = y;
    potting[potID].sprite.w = size;
    potting[potID].sprite.h = size;

    set_sprite_tile(spriteID,0);
    potting[potID].sprite.ID[0] = 0;
    set_sprite_tile(spriteID + 1,1);
    potting[potID].sprite.ID[1] = 1;
    set_sprite_tile(spriteID + 2,2);
    potting[potID].sprite.ID[2] = 2;
    set_sprite_tile(spriteID + 3,3);
    potting[potID].sprite.ID[3] = 3;

    spriteMovment(&potting, potting[potID].sprite.x, potting[potID].y);
}

//setup sprites, widow, and background
void init(){
    UINT8 counter = 0;
    UINT8 x = 20;
    UINT8 y = 17;
    set_sprite_data(0,4, pots);
    
    while (counter < 8){
        setupPot(x,y,counter);
        x -= 20;
        y -= 18;
        counter ++;
    }
    set_bkg_data(0, 3, shelf);
    set_bkg_tiles(0,0,20,18,bkg_map);
    

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}

//main
void main(){
    init();
}
