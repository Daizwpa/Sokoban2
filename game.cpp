/*
* name file : game.cpp

* By: ziad bennadj

* Role :

* Date of production 15 07 2018

**************************************/

#include "game.h"
#include "file.h"
#include "graphices.h"

int play(SDL_Surface *window, int number_level){
    // declare
    SDL_Surface *next = NULL, *win = NULL;
    pos_mario mario_now = {0,0}; // Coordinate mario in map
    format position = DOWN;
    plane Map[NB_BLOCK_WIDTH][NB_BLOCK_HIGHT] = {EMPTY};
    SDL_Event event;
    SDL_Rect coordinate_menu = {0};
    int i = 0, j = 0, loop = 0;
    int next_ok = 0, up = 0;
    static int level = 1;


    // getting Map
    if(get_map(Map, level)){Error("map not available please check file level.lel");}

    // check if some problem in map
    if  ( check_map(Map, &mario_now) ){ Error("error map");}

    // graphics before
    graphics( window, Map, position);

    // MAIN LOOP
    while(!loop){
        SDL_WaitEvent(&event);
        switch(event.type){
        case SDL_QUIT :
            return 1;
            break;
        case SDL_KEYDOWN :
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE :
                loop = 1;
                return EXIT_SUCCESS;
                up = 1;
                break;
            case SDLK_UP :
                position = UP;
                up = 1;
                move_mario(Map, position, &mario_now);
                break;
            case SDLK_DOWN :
                position = DOWN;
                up = 1;
                move_mario(Map, position, &mario_now);
                break;
            case SDLK_LEFT :
                position = LEFT;
                up = 1;
                move_mario(Map, position, &mario_now);
                break;
            case SDLK_RIGHT :
                position = RIGHT;
                up = 1;
                move_mario(Map, position, &mario_now);
                break;
            }// END switch key------------
            case SDL_KEYUP :
                up = 0;
            break;

        }// END switch event-------------
        graphics( window, Map, position);
        loop = winner(Map, loop);

    }// END while c

    if(level == number_level)
    {
        loop = 0;
        win = IMG_Load("wine.png");
        SDL_BlitSurface(win, NULL, window,&coordinate_menu );
        SDL_Flip(window);

        while(!loop){
            SDL_WaitEvent(&event);
            switch(event.type){
            case SDL_QUIT :
                return 1;
                break;
            case SDL_KEYDOWN :
                loop = 1;
                break;
            }// END switch event-------------

        }// END while c

        exit(EXIT_SUCCESS);

    }
    else
    {
        if(level < number_level){
            // ask player if he want play
            loop = 0;
            next = IMG_Load("next.png");
            SDL_BlitSurface(next, NULL, window,&coordinate_menu );
            SDL_Flip(window);

            while(!loop){
                SDL_WaitEvent(&event);
                switch(event.type){
                case SDL_QUIT :
                    return 1;
                    break;
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        loop = 1;
                        break;
                    case SDLK_n :
                        loop = 1;
                        next_ok = 1;
                        level ++;

                    }// END switch key------------

                }// END switch event-------------

            }// END while c
            loop = 0;
            if(next_ok ){//  for next level ---------------------------------------------------------------------------------
                next_ok = 0;
                next_level(window, number_level);// start on line number 20
            }

        }

    }

    return EXIT_SUCCESS;

}//END OF FUNCTION PLAY ------------------------------------------------------------------------------------------------*/

int check_map(plane M[][NB_BLOCK_HIGHT],pos_mario *pos){
    //declare
    int mario_here = 0, object_here = 0,box_here =0;
    int i = 0, j = 0;

    // find mario and Object
    for(i = 0; i< NB_BLOCK_WIDTH; i++){

        for(j = 0; j< NB_BLOCK_HIGHT; j++){
            switch(M[i][j]){
            case MARIO :
                pos->x = i;
                pos->y = j;
                mario_here++;
                break;
            case OBJECT :
                object_here++;
                break;
            case BOX :
                box_here++;
                break;




            }// end switch(M)
        }// end for(j)
    }// end for(i)
    if (mario_here != 1){
        Error("Error map mario");
    }
    if (object_here == 0 ){
        Error("Error map object");
    }
    if(box_here < object_here){
        Error("Error map object");
    }
    return EXIT_SUCCESS;
}// END  check map----------------------------------------------------------------------

void move_mario(plane M[][NB_BLOCK_HIGHT], format P, pos_mario *C ){
    switch(P){
    case UP :

       if( C->y-1 < 0 )
        break;

       if( M[C->x][C->y-1] == WALL )
        break;

       if(( ( (M[C->x][C->y-1] == BOX) || (M[C->x][C->y-1] == BOXOK) )&& C->y-2 < 0 ) || (  ( (M[C->x][C->y-1] == BOX) || (M[C->x][C->y-1] == BOXOK) )&&( (M[C->x][C->y-2] == BOX) || (M[C->x][C->y-2] == BOXOK ) || (M[C->x][C->y-2] == WALL) ) ) )
        break;
        if(M[C->x][C->y] == MARIO_WITH_OBJECT )
        {

            if(M[C->x][C->y - 1] == BOXOK){
               if(M[C->x][C->y-2] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y-1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y-2] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y-1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y-2] = BOX;

                }


            }
            if(M[C->x][C->y - 1] == BOX ){
                if(M[C->x][C->y-2] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y-1] = MARIO  ;
                    M[C->x][C->y-2] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y-1] = MARIO;
                    M[C->x][C->y-2] = BOX;
                }

            }
            if(M[C->x][C->y - 1] == OBJECT){
                M[C->x][C->y] = OBJECT ;
                M[C->x][C->y-1] = MARIO_WITH_OBJECT ;

            }
            if(M[C->x][C->y - 1] == EMPTY){

                M[C->x][C->y] = OBJECT ;
                M[C->x][C->y-1] = MARIO ;
            }

            C->y--;
        }
        else
        {
            if(M[C->x][C->y] == MARIO)
            {
                if(M[C->x][C->y - 1] == BOXOK){
               if(M[C->x][C->y-2] == OBJECT){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y-1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y-2] = BOXOK;

                }else{
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y-1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y-2] = BOX;

                }


            }
                if(M[C->x][C->y - 1] == BOX ){
                if(M[C->x][C->y-2] == OBJECT){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y-1] = MARIO  ;
                    M[C->x][C->y-2] = BOXOK;

                }else{
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y-1] = MARIO;
                    M[C->x][C->y-2] = BOX;
                }

            }
                if(M[C->x][C->y - 1] == OBJECT){
                M[C->x][C->y] = EMPTY ;
                M[C->x][C->y-1] = MARIO_WITH_OBJECT ;

            }
                if(M[C->x][C->y - 1] == EMPTY){
                M[C->x][C->y] = EMPTY ;
                M[C->x][C->y-1] = MARIO ;
            }
            }

            C->y--;
        }

        break;
    case DOWN :

        if( C->y+1 > 11 )
        break;

        if( M[C->x][C->y+1] == WALL )
        break;

        if(( ( (M[C->x][C->y+1] == BOX) || (M[C->x][C->y+1] == BOXOK) )&& C->y+2 > 11 ) || (  ( (M[C->x][C->y+1] == BOX) || (M[C->x][C->y+1] == BOXOK) )&&( (M[C->x][C->y+2] == BOX) || (M[C->x][C->y+2] == BOXOK ) || (M[C->x][C->y+2] == WALL) ) ) )
        break;

        if(M[C->x][C->y] == MARIO_WITH_OBJECT )
        {

            if(M[C->x][C->y + 1] == BOXOK){
               if(M[C->x][C->y+2] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y+1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y+2] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y+1] = MARIO_WITH_OBJECT  ;
                    M[C->x][C->y+2] = BOX;

                }


            }
            if(M[C->x][C->y + 1] == BOX ){
                if(M[C->x][C->y+2] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y+1] = MARIO  ;
                    M[C->x][C->y+2] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x][C->y+1] = MARIO;
                    M[C->x][C->y+2] = BOX;
                }

            }
            if(M[C->x][C->y + 1] == OBJECT){
                M[C->x][C->y] = OBJECT ;
                M[C->x][C->y+1] = MARIO_WITH_OBJECT ;

            }
            if(M[C->x][C->y + 1] == EMPTY){
                M[C->x][C->y] = OBJECT ;
                M[C->x][C->y+1] = MARIO ;
            }


            C->y++;
        }
        else
        {
            if(M[C->x][C->y] == MARIO){
                if(M[C->x][C->y + 1] == BOXOK){
                    if(M[C->x][C->y+2] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x][C->y+1] = MARIO_WITH_OBJECT  ;
                        M[C->x][C->y+2] = BOXOK;

                    }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x][C->y+1] = MARIO_WITH_OBJECT  ;
                        M[C->x][C->y+2] = BOX;

                    }


                }
                if(M[C->x][C->y + 1] == BOX ){
                   if(M[C->x][C->y+2] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x][C->y+1] = MARIO  ;
                        M[C->x][C->y+2] = BOXOK;

                    }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x][C->y+1] = MARIO;
                        M[C->x][C->y+2] = BOX;
                    }

            }
                if(M[C->x][C->y + 1] == OBJECT){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y+1] = MARIO_WITH_OBJECT ;

                }
                if(M[C->x][C->y + 1] == EMPTY){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x][C->y+1] = MARIO ;
                }
            }

            C->y++;

        }


        break;
    case LEFT :

        if( C->x-1 < 0 )
        break;

        if( M[C->x-1][C->y] == WALL )
        break;

        if(( ( (M[C->x-1][C->y] == BOX) || (M[C->x-1][C->y] == BOXOK) )&& C->x-2 < 0 ) || (  ( (M[C->x-1][C->y] == BOX) || (M[C->x-1][C->y] == BOXOK) )&&( (M[C->x-2][C->y] == BOX) || (M[C->x-2][C->y] == BOXOK ) || (M[C->x-2][C->y] == WALL) ) ) )
        break;

        if(M[C->x][C->y] == MARIO_WITH_OBJECT )
        {

            if(M[C->x - 1][C->y] == BOXOK){
               if(M[C->x - 2][C->y] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x - 1][C->y] = MARIO_WITH_OBJECT  ;
                    M[C->x - 2][C->y] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x - 1][C->y] = MARIO_WITH_OBJECT  ;
                    M[C->x - 2 ][C->y] = BOX;

                }


            }
            if(M[C->x - 1 ][C->y] == BOX ){
                if(M[C->x - 2][C->y] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x - 1][C->y] = MARIO  ;
                    M[C->x - 2][C->y] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x - 1][C->y] = MARIO;
                    M[C->x - 2][C->y] = BOX;
                }

            }
            if(M[C->x - 1][C->y ] == OBJECT){
                M[C->x][C->y] = OBJECT ;
                M[C->x - 1][C->y] = MARIO_WITH_OBJECT ;

            }
            if(M[C->x - 1][C->y] == EMPTY){
                M[C->x][C->y] = OBJECT ;
                M[C->x - 1][C->y] = MARIO ;
            }


            C->x--;
        }
        else
        {
            if(M[C->x][C->y] == MARIO){
                if(M[C->x - 1][C->y] == BOXOK){
                    if(M[C->x - 2][C->y] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x - 1][C->y] = MARIO_WITH_OBJECT  ;
                        M[C->x - 2][C->y] = BOXOK;

                    }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x - 1][C->y] = MARIO_WITH_OBJECT  ;
                        M[C->x - 2][C->y] = BOX;

                    }


                }
                if(M[C->x - 1][C->y] == BOX ){
                    if(M[C->x - 2][C->y] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x - 1][C->y] = MARIO  ;
                        M[C->x - 2][C->y] = BOXOK;

                }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x - 1][C->y] = MARIO;
                        M[C->x - 2][C->y] = BOX;
                    }

                }
                if(M[C->x - 1][C->y] == OBJECT){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x - 1][C->y] = MARIO_WITH_OBJECT ;

                }
                if(M[C->x - 1][C->y] == EMPTY){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x - 1][C->y] = MARIO ;
                }
            }

            C->x--;
        }




        break;
    case RIGHT :

        if( C->x+1 > 11 ){
            fprintf(stderr, "503");
        break;
        }

        if( M[C->x+1][C->y] == WALL ){
           fprintf(stderr, "507");

           break;
        }


        if(( ( (M[C->x+1][C->y] == BOX) || (M[C->x+1][C->y] == BOXOK) )&& C->x+2 >= 11 ) || (  ( (M[C->x+1][C->y] == BOX) || (M[C->x+1][C->y] == BOXOK) )&&( (M[C->x+2][C->y] == BOX) || (M[C->x+2][C->y] == BOXOK  )|| (M[C->x+2][C->y] == WALL) ) ) )
       {
           fprintf(stderr, "516");
           break;
       }


        if(M[C->x][C->y] == MARIO_WITH_OBJECT )
        {

            if(M[C->x + 1][C->y] == BOXOK){
               if(M[C->x + 2][C->y] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x + 1][C->y] = MARIO_WITH_OBJECT  ;
                    M[C->x + 2][C->y] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x + 1][C->y] = MARIO_WITH_OBJECT  ;
                    M[C->x + 2 ][C->y] = BOX;

                }


            }
            if(M[C->x + 1 ][C->y] == BOX ){
                if(M[C->x + 2][C->y] == OBJECT){
                    M[C->x][C->y] = OBJECT ;
                    M[C->x + 1][C->y] = MARIO  ;
                    M[C->x + 2][C->y] = BOXOK;

                }else{
                    M[C->x][C->y] = OBJECT ;
                    M[C->x + 1][C->y] = MARIO;
                    M[C->x + 2][C->y] = BOX;
                }

            }
            if(M[C->x + 1][C->y ] == OBJECT){
                M[C->x][C->y] = OBJECT ;
                M[C->x + 1][C->y] = MARIO_WITH_OBJECT ;

            }
            if(M[C->x + 1][C->y] == EMPTY){
                M[C->x][C->y] = OBJECT ;
                M[C->x + 1][C->y] = MARIO ;
            }

            fprintf(stderr, "562");
            C->x++;
        }
        else
        {


            if(M[C->x][C->y] == MARIO){
                if(M[C->x + 1][C->y] == BOXOK){
                    if(M[C->x + 2][C->y] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x + 1][C->y] = MARIO_WITH_OBJECT  ;
                        M[C->x + 2][C->y] = BOXOK;

                    }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x + 1][C->y] = MARIO_WITH_OBJECT  ;
                        M[C->x + 2][C->y] = BOX;

                    }


                }
                if(M[C->x + 1][C->y] == BOX ){
                    if(M[C->x + 2][C->y] == OBJECT){
                        M[C->x][C->y] = EMPTY ;
                        M[C->x + 1][C->y] = MARIO  ;
                        M[C->x + 2][C->y] = BOXOK;

                    }else{
                        M[C->x][C->y] = EMPTY ;
                        M[C->x + 1][C->y] = MARIO;
                        M[C->x + 2][C->y] = BOX;
                    }

                }
                if(M[C->x + 1][C->y] == OBJECT){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x + 1][C->y] = MARIO_WITH_OBJECT ;

                }
                if(M[C->x + 1][C->y] == EMPTY){
                    M[C->x][C->y] = EMPTY ;
                    M[C->x + 1][C->y] = MARIO ;
                }
            }

            C->x++;

        }


        break;
    }//end switch-------------
}// END move_mario()------------------------------------------------------------------------------------

int winner(plane Map[][NB_BLOCK_HIGHT], int coun){
    //declare
    int i = 0, j = 0;
    int object_here = 0;
    if(coun){
        return coun;

    }else{

        // find mario and Object
        for(i = 0; i< NB_BLOCK_WIDTH; i++){
            for(j = 0; j< NB_BLOCK_HIGHT; j++){

                if( Map[i][j] == OBJECT || Map[i][j] == MARIO_WITH_OBJECT){
                    object_here++;
                }

            }
        }
        if (!object_here){
            return 1; // for end the game
        }
        return EXIT_SUCCESS;
    }
}//end winner

void next_level(SDL_Surface *w, int nu_level){
    play(w, nu_level);
}

