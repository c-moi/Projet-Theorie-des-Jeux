#ifndef H_PA_MAIN
#define H_PA_MAIN

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct move {
    char position[3]; 
    int joueur; // joueur qui a joué le coup (1 jeton noir ou 2 jeton blanc)

    struct move *suiv;
    struct move *prec;
} Move;

#endif



/// partie Manon

///void respectRegles();


// ----------------------------------------------------------------------------------------------
// - prototypes de la gestion d'historique de coups ---------------------------------------------

Move *creatMaillon(int joueur, char position[3]);
Move *insTT(Move *L, Move *moves);
void printMoveHistory(Move *L, Move *actuel);
Move *deplacArriere(Move *actuel);
Move *deplacAvant(Move *actuel, Move *L);
void supprimCoupApres(Move *actuel);

// ----------------------------------------------------------------------------------------------