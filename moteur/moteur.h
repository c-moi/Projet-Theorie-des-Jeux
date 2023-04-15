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
// - import des fonctions de joueur -------------------------------------------------------------

#include "../joueur/joueur.h"

#ifndef H_PA_JOUEUR
#define H_PA_JOUEUR

char* configPlayers(Move* move, char rep[3]);

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes securisation des actions du joueur sur le jeu -----------------------------------

#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR

typedef struct paramJeu
{
    int nbJoueurs;
    int lvlOrdi;
    int tourJoueur;

} parametres;

void moteurJeu(Move *liste);
Move* initPlto(Move* liste, Move* LN, Move* LB);

Move* creatMaillon(int joueur, char position[3]);
Move* insTT(Move *L, Move *moves);
Move* deplacFin(Move *L);

Move* respectRegles(Move* Liste, Move* Maillon);
void verifContour(char rep[3],Move *LG, Move *List_J1, Move *List_J2, int pre);
void verifSuite(char rec[3], char rep[3], Move *Liste, int pre);

Move *deplacArriere(Move *actuel);
Move *deplacAvant(Move *actuel);
void printMoveHistory(Move *L, Move *actuel);
void supprimCoupApres(Move *actuel);

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes de la gestion d'historique de coups ---------------------------------------------

#ifndef H_PA_HISTORY
#define H_PA_HISTORY





#endif
// ----------------------------------------------------------------------------------------------