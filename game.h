/*
* name file : game.h

* By: ziad bennadj

* Role : for all constants of the project

* Date of production 15 07 2018

**************************************************/

#ifndef DEF_GAME
#define DEF_GAME
#include "constant.h"

    int play(SDL_Surface *window, int number_level);

    int check_map(plane Map[][NB_BLOCK_HIGHT],pos_mario *pos);

    void move_mario(plane M[][NB_BLOCK_HIGHT], format P, pos_mario *C );

    int winner(plane Map[][NB_BLOCK_HIGHT], int c);

    void next_level(SDL_Surface *w, int nu_level);

#endif // DEF_GAME
