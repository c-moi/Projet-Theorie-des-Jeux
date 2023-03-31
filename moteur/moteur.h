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
// - import pour la gestion des fichiers --------------------------------------------------------

#ifndef H_PA_FICHIERS
#define H_PA_FICHIERS

#include "../fichier/fichier.h"

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes securisation des actions du joueur sur le jeu -----------------------------------

#ifndef H_PA_REGLES
#define H_PA_REGLES

#include "../joueur/joueur.h"

void respectRegles(char rep[3], Move *LG, Move *L);
void verifContour(char rep[3],Move *LG, Move *List_J1, Move *List_J2, int pre);
void verifSuite(char rec[3], char rep[3], Move *Liste, int pre);

void respectRegles(char rep[3]);
void verifContour(char rep[3]);

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes de la gestion d'historique de coups ---------------------------------------------

#ifndef H_PA_HISTORY
#define H_PA_HISTORY

Move *creatMaillon(int joueur, char position[3]);
Move *insTT(Move *L, Move *moves);
void printMoveHistory(Move *L, Move *actuel);
Move *deplacArriere(Move *actuel);
Move *deplacAvant(Move *actuel, Move *L);
void supprimCoupApres(Move *actuel);
Move *chargerHistorique();

#endif
// ----------------------------------------------------------------------------------------------