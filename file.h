/*
* name file : file.h

* By: ziad bennadj

* Role : define function in file.c

* Date of production 18 07 2018

**********************************/

#ifndef DEF_FE
#define DEF_FE
#include "constant.h"

    int get_map(plane M[][NB_BLOCK_HIGHT], int L);

    void save(plane M[][NB_BLOCK_HIGHT]);

    int check_level();

#endif // DEF_FE
