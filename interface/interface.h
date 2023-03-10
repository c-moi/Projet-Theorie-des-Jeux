#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../moteur/moteur.h"
//#include "../structure.h"


#endif

typedef struct move 
{
    char posi[3]; // position
    char joueur[6]; // joueur qui a joué le coup (blanc ou noir)
    struct move *suiv;
} Move;


Move *initAction();
Move *insTT(Move *L, Move *moves);

void affichQua (void);
Move* rempTab2 (char val[8][8]);
void rempTab (void);

