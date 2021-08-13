/*
* name file : file.c

* By: ziad bennadji

* Role : read and writ file

* Date of production 18 07 2018

*************************************/

#include "constant.h"

int get_map( plane M[][NB_BLOCK_HIGHT], int L){// i should check this function
    // declare
    int i = 0, j = 0;
    FILE* level = NULL;
    char string_map[ NB_BLOCK_HIGHT * NB_BLOCK_WIDTH +1];
    //end declare ---------------------------------------

    level = fopen("level.lvl", "r");
    if ( !level ){Error("Error file");}

    for(i = 0; i<L; i++){
       fgets(string_map, (NB_BLOCK_HIGHT * NB_BLOCK_WIDTH) +1, level);
       fgetc(level);
    }


    // piling map-------------------------------

    for(i = 0; i< NB_BLOCK_WIDTH; i++){

        for(j = 0; j< NB_BLOCK_HIGHT; j++){
            switch(string_map[(i * NB_BLOCK_WIDTH) + j]){
            case '0' :
                M[j][i] = EMPTY;
                break;
            case '1' :
                M[j][i] = BOX;
                break;
            case '2' :
                M[j][i] = BOXOK;
                break;
            case '3' :
                M[j][i] = OBJECT;
                break;
            case '4' :
                M[j][i] = WALL;
                break;
            case '5' :
                M[j][i] = MARIO;
                break;

            }
        }
    }
    fclose(level);
    return EXIT_SUCCESS;

}// END GET_MAP --------------------------------------

void save(plane M[][NB_BLOCK_HIGHT]){
    // declare --------------------
    FILE *level = NULL;
    int i = 0, j = 0;
    // end declare -----------------

    // open file
    level = fopen("level.lvl","a");
    if(!level){Error("Error read file");}

    // write on file level
    for(i = 0; i<NB_BLOCK_WIDTH; i++){
        for( j = 0; j<NB_BLOCK_HIGHT; j++){
           fprintf(level, "%d",M[j][i]);
        }
    }

    fputc('\n', level);
    // freeing file
    fclose(level);
}//end save

int check_level(){
    // declare
    FILE* file_level = NULL;
    char c ;
    char string_map[ NB_BLOCK_HIGHT * NB_BLOCK_WIDTH +1];
    int number_level = 0;

    // open file
    file_level = fopen("level.lvl", "r");
    if ( !file_level ){Error("Error file");}

    // check level
    while( fgets( string_map, NB_BLOCK_HIGHT*NB_BLOCK_WIDTH +1 , file_level) != NULL ){
       number_level++;
       fgetc( file_level);
    }

    return number_level;
}// end check _level
