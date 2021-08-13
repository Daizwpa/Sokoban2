#ifndef DEF_CONST
#define DEF_CONST

    // add library
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <SDL.h>
    #include    <SDL_ttf.h>
    #include    <SDL_image.h>

    // values define
    #define     WINDOW_WIDTH         800
    #define     WINDOW_HIGHT         600

    // Macro define
    #define     Error( message , type  )    if( type == SDL) fprintf(stderr , "%s :%s\n", message, SDL_GetError() );\
                                            else fprintf(stderr , "%s :%s\n", message, TTF_GetError() );\
                                            exit( EXIT_FAILURE );
    // enumerations
    enum { SDL, SDL_TTF };

#endif // DEF_CONST
