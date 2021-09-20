// gdbk include
#include <gb/gb.h>
#include <stdio.h>
#include "shelf.c"
#include "bkg.c"

//setup sprites, widow, and background
void init(){
    set_bkg_data(0, 3, shelf);
    set_bkg_tiles(0,0,20,18,bkg_map);
    SHOW_BKG;
    DISPLAY_ON;
}

//main
void main(){
    init();
}
