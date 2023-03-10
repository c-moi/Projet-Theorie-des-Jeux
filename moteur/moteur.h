#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../structure.h"

#endif


#include "../interface/interface.h"
/// partie Manon

void respectRegles();


/// partie Latifa

typedef struct move 
{
    char posi[3]; // position
    char joueur[6]; // joueur qui a joué le coup (blanc ou noir)
    struct move *suiv;
} Move;


Move *initAction();
Move *insTT(Move *L, Move *moves);
void printMoveHistory(Move *L);