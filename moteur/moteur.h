#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif



/// partie Manon

///void respectRegles();

/// partie Latifa

typedef struct move {
    char position[3]; 
    int joueur; // joueur qui a joué le coup (1 jeton noir ou 2 jeton blanc)
    struct move *suiv;
    struct move *prec;
} Move;

Move *initAction(int joueur, char position[3]);
Move *insTT(Move *L, Move *moves);
void printMoveHistory(Move *L, Move *actuel);
Move *deplacArriere(Move *actuel);
Move *deplacAvant(Move *actuel, Move *L);
void supprimCoupApres(Move *actuel);