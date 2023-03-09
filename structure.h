#ifndef MAIN
#define MAIN

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#endif

typedef struct move {
    char posi[3];
    int joueur; // joueur qui a joué le coup (1 ou 2)
    struct move *suiv;
    struct move *prec;
} Move;