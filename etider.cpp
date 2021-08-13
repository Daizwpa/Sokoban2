/*
* name file : main.c

* By: ziad bennadj

* Role : for editor

* Date of production 18 07 2018

**************************************/
#include "file.h"
#include "graphices.h"
#include "etider.h"
#include "constant.h"

int editor(SDL_Surface *window){
    // declare
    int  c = 0, thing = MARIO, key_up = 0;
    plane Map[NB_BLOCK_WIDTH][NB_BLOCK_HIGHT] = {EMPTY};
    SDL_Event event;
    SDL_Rect coor_mouse = {0}; // for save coordinate mouse
    SDL_WarpMouse(window->w / 2, window->h / 2);
    coor_mouse.x = (window->w /2) - 17;
    coor_mouse.y = (window->h / 2) - 17;



    // MAIN LOOP
    while(!c){
        SDL_WaitEvent(&event);
        switch(event.type){
        case SDL_QUIT :
            return 1;
            break;
        case SDL_MOUSEBUTTONUP :
            switch(event.button.button){
            case SDL_BUTTON_LEFT :
                Map[event.button.x/BLOCK_WIDTH][event.button.y/BLOCK_WIDTH] = (plane) thing;
                break;
            case SDL_BUTTON_RIGHT :
                Map[event.button.x/BLOCK_WIDTH][event.button.y/BLOCK_WIDTH] = EMPTY;
                break;
            case SDL_BUTTON_WHEELDOWN :
                thing++;
                if(thing == EMPTY || thing == 6){
                    thing = BOX;
                }
                break;
            case SDL_BUTTON_WHEELUP :
                thing--;
                if(thing == EMPTY || thing == 6){
                    thing = MARIO;
                }
                break;
            }// end switch event button -----------
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
            case SDLK_s :
                save(Map);
                key_up = 1;
                break;
            case SDLK_ESCAPE:
                c = 1;
                save(Map);
                break;

            break;
            }// end switch key
        case SDL_KEYUP :

            key_up = 0;
            break;

        case SDL_MOUSEMOTION :
            coor_mouse.x = event.motion.x - 17;
            coor_mouse.y = event.motion.y - 17;
            break;

        }// END switch event-------------
        graphics( window, Map, DOWN);
        show_thing( window, thing, &coor_mouse);

    }// END while c

    return EXIT_SUCCESS;
}//END editor

void show_thing(SDL_Surface *W, int th, SDL_Rect *coor){

    SDL_Surface *thing = NULL;
    // balling Surface

    switch(th){
    case WALL :
        thing = IMG_Load("wall.jpg");
        break;
    case BOX :
        thing = IMG_Load("box.jpg");
        break;
    case BOXOK :
        thing = IMG_Load("boxok.jpg ");
        break;
    case OBJECT :
        thing = IMG_Load("object.png");
        break;
    case MARIO :
        thing = IMG_Load("mario_down.gif ");
        break;
    }
    // make center
    SDL_BlitSurface(thing, NULL, W, coor);
    SDL_Flip(W);
    SDL_FreeSurface(thing);
}

void menu_explained(SDL_Surface *W, int select){
    // declare
    SDL_Rect coor = {0};
    SDL_Surface *menu = NULL;
    SDL_Event event ;
    int loop = 0;

    switch(select){

    case PLAY :
        menu = IMG_Load("menu_play.jpg");
        break;
    case EDITOR :
        menu = IMG_Load("menu_explained.jpg");
        break;
    }// end switch select

    SDL_BlitSurface(menu, NULL, W, &coor);

    SDL_Flip(W);

    SDL_FreeSurface(menu);

    while( !loop ){

        SDL_WaitEvent(&event);

        switch(event.type){

        case SDL_KEYDOWN :
           loop = 1;
           break;
        }// end switch

    }// end while

}
