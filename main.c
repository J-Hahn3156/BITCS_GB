// gdbk include
#include <gb/gb.h>
#include <stdio.h>
#include "shelf.c"
#include "bkg.c"
#include "pots.c"
#include "meta_sprite.c"

struct metaSprite potting;

spriteMovment(struct metaSprite* sp, UINT8 x, UINT8 y){
    move_sprite(sp->ID[0], x, y);
    move_sprite(sp->ID[1], x + 8, y);
    move_sprite(sp->ID[2], x, y + 8);
    move_sprite(sp->ID[3], x + 8, y + 8);
}

void setupPot(){
    potting.x = 20;
    potting.y = 17;
    potting.w = 16;
    potting.h = 16;

    set_sprite_tile(0,0);
    potting.ID[0] = 0;
    set_sprite_tile(1,1);
    potting.ID[1] = 1;
    set_sprite_tile(2,2);
    potting.ID[2] = 2;
    set_sprite_tile(3,3);
    potting.ID[3] = 3;

    spriteMovment(&potting, potting.x, potting.y);
}

//setup sprites, widow, and background
void init(){
    set_sprite_data(0,4, pots);
    set_bkg_data(0, 3, shelf);
    set_bkg_tiles(0,0,20,18,bkg_map);
    setupPot();

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}

//main
void main(){
    init();
}
