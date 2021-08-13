/*
* name file : main.c

* By: ziad bennadj

* Role :

* Date of production 15 07 2018

****************************************/

#include "constant.h"
#include "game.h"
#include "graphices.h"
#include "etider.h"
#include "file.h"

int main ( int argc, char** argv )
{
    /* declare */
    SDL_Surface* screen = NULL, *menu = NULL;
    SDL_Rect position;
    int loop = 0, number_level = 0;
    SDL_Event event;
    /*----------------------------------------*/
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){ Error("Unable to init SDL: %s\n");}

    // create a new window
    SDL_WM_SetIcon(IMG_Load("icon.png"), NULL);
    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HIGHT, 32, SDL_HWSURFACE| SDL_DOUBLEBUF);
    if ( !screen ){Error("Unable to set WINDOW_WIDTH * WINDOW_HIGTH video: %s\n");}
    SDL_WM_SetCaption("Sokoban", NULL);

    // create a new menu
    position.x = 0;
    position.y = 0;
    menu = IMG_Load("menu.jpg");

    // Main lOOP
    while( !loop ){
        SDL_WaitEvent(&event);
        switch(event.type){
        case SDL_QUIT ://--------------------------------------------

            loop = 1;
            break;

        case SDL_KEYDOWN :
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE ://-------------------------------------

                loop = 1;
                break;

            case SDLK_KP1 ://----------------------------------------

                number_level =  check_level();
                if( number_level == 0 )
                {
                    Error("there isn't level in file level.lvl");
                }
                menu_explained(screen, PLAY);// play here for select image which upload in screen
                loop =  play(screen, number_level);
                break;

            case SDLK_KP2 ://-----------------------------------------

               menu_explained(screen, EDITOR);
                loop = editor(screen);
                break;

            }// end of switch
            break;

        }//end of switch
        // clear window
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 10, 10, 10));
        SDL_BlitSurface(menu, NULL, screen, &position);
        SDL_Flip(screen);

    }// end of while

    // freeing memory
    SDL_FreeSurface(menu);
    SDL_Quit();
    return EXIT_SUCCESS;
}
