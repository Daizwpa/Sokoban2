/*
* name file : constant.h

* By: ziad bennadj

* Role : constant and header for all file .h of program

* Date of production 15 07 2018

**********************************/

#ifndef DEF_CONSTANT

#define DEF_CONSTANT

    #include      <string.h>

    #include      <stdio.h>

    #include      <stdlib.h>

    #include      <SDL.h>

    #include      <SDL_image.h>

    #define       NB_BLOCK_HIGHT      12

    #define       NB_BLOCK_WIDTH      12

    #define       BLOCK_HIGHT         34

    #define       BLOCK_WIDTH         34

    #define       WINDOW_HIGHT        NB_BLOCK_HIGHT  *   BLOCK_HIGHT

    #define       WINDOW_WIDTH        NB_BLOCK_WIDTH  *   BLOCK_WIDTH

    #define       Error(massge)  fprintf(stderr, "%s : %s\n", massge, SDL_GetError() );\
    exit(EXIT_FAILURE);


    enum format { UP, DOWN, LEFT, RIGHT};
    typedef enum format format;


    enum plane { EMPTY, BOX, BOXOK, OBJECT, WALL, MARIO, MARIO_WITH_OBJECT};
    typedef enum plane plane;

    enum { PLAY, EDITOR};

    typedef struct pos_mario pos_mario;
    struct pos_mario{

        int x;

        int y;

    };



#endif // DEF_CONSTANT
