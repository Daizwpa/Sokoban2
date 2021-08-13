#include "constant.h"

int main ( int argc, char** argv )
{
    /* declare */
    int loop = 0;
    SDL_Surface* screen = NULL;
    SDL_Rect position;
    SDL_Event event;
    SDL_Color white = {255, 255, 255, 255};
    /*----------------------------------------*/
    // initialize SDL video and SDL_ttf
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){ Error( "Unable to init SDL: %s\n", SDL ); }
    if (TTF_Init() == EOF){ Error( "Unable to init SDL: %s\n", SDL_TTF );   }
    /*--------------------------------------------------------------------------*/

    // create a new window and upload font
    screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HIGHT, 32, SDL_HWSURFACE| SDL_DOUBLEBUF);
    if ( !screen ){ Error( "Unable to set WINDOW_WIDTH * WINDOW_HIGTH video", SDL ); }
    SDL_WM_SetCaption( "Window" , NULL);
    /*-----------------------------------------------------------------------------------------*/

    // Main lOOP
    while( !loop ){

        SDL_PollEvent( &event );// wait event;

        switch( event.type ){
        case SDL_QUIT :

          loop = 1;
          break;

        case SDL_KEYDOWN :

          switch( event.key.keysym.sym ){
            case SDLK_ESCAPE :

              loop = 1;
              break;

          }// end of switchn event.key.keysym.sym
          break;

        }//end of switch event.type

        // clear window
        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 10, 10, 10) );

        // flip surface
        SDL_BlitSurface(text, NULL, screen, &position_text);
        SDL_BlitSurface( person, NULL, screen, &position);
        SDL_Flip( screen );

    }// end  while loop

    // freeing memory
    TTF_Quit();
    SDL_Quit();
    /*-----------------------*/

    return EXIT_SUCCESS;
}
