/*
* name file : graphices.c

* By: ziad bennadj

* Role : this file will be drop map

* Date of production 18 07 2018
*********************************************/

#include "graphices.h"

void graphics( SDL_Surface *W, plane M[][NB_BLOCK_HIGHT], format format_mario){

    // declare
    SDL_Surface *mario[4]={NULL}, *wall = NULL, *box =NULL, *boxok = NULL, *object = NULL;
    int i = 0, j = 0;
    SDL_Rect position ;
    position.x = 0;
    position.y = 0;

    // balling Surface
    wall = IMG_Load("wall.jpg");
    box = IMG_Load("box.jpg");
    boxok = IMG_Load("boxok.jpg ");
    object = IMG_Load("object.png");
    mario[UP] = IMG_Load("mario_up.gif ");
    mario[DOWN] = IMG_Load("mario_down.gif ");
    mario[LEFT] = IMG_Load("mario_left.gif ");
    mario[RIGHT] = IMG_Load("mario_right.gif ");
    /* END UPLOAD ---------------------------------------*/
    SDL_FillRect(W, NULL, SDL_MapRGB(W->format, 0, 0, 0) );

    for(i = 0; i<NB_BLOCK_WIDTH; i++){
        for(j = 0; j<NB_BLOCK_HIGHT; j++){
            switch(M[i][j]){
            case MARIO :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(mario[format_mario], NULL, W, &position);
                break;
            case WALL :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(wall, NULL, W, &position);
                break;
            case BOX :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(box, NULL, W, &position);
                break;
            case BOXOK :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(boxok, NULL, W, &position);
                break;
            case OBJECT :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(object, NULL, W, &position);
                break;
            case MARIO_WITH_OBJECT :
                position.x = i*BLOCK_WIDTH;// local structure
                position.y = j*BLOCK_HIGHT;// local structure
                SDL_BlitSurface(object, NULL, W, &position);
                SDL_BlitSurface(mario[format_mario], NULL, W, &position);

                break;
            }
        }
    }
    SDL_Flip(W);


    //freeing memory
    SDL_FreeSurface(wall);
    SDL_FreeSurface(box);
    SDL_FreeSurface(boxok);
    SDL_FreeSurface(object);
    for(i = 0; i<4; i++){
        SDL_FreeSurface(mario[i]);
    }
    // END FREEING ----------------------*/

}//END graphics()
