// ----------------------------------------------------------------------------------------------
// - elements necessaires au bon fonctionnement du programme en general -------------------------

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

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import algorithme de l'IA ------------------------------------------------------------------

#ifndef H_PA_IA
#define H_PA_IA

#include "../IA/IA.h"

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes configuration du/des joueurs ----------------------------------------------------

#ifndef H_PA_PROTO_JOUEUR
#define H_PA_PROTO_JOUEUR

char* configPlayers(Move *move, char rep[3]);
char* lancerPartie(Move *move, char rep[3]);

#endif

// ----------------------------------------------------------------------------------------------