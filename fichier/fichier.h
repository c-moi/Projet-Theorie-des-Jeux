// ----------------------------------------------------------------------------------------------
// - elements necessaires au bon fonctionnement du programme en general -------------------------

#ifndef H_PA_MAIN
#define H_PA_MAIN

#include "../globals.h"

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes gestion des fichiers ------------------------------------------------------------

#ifndef H_PA_FICHIER
#define H_PA_FICHIER

Move *chargerHistorique(Move* Liste);
void sauvegarderHistorique (Move *L, Move *actuel);


#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - remplissage de la liste des coups joués ----------------------------------------------------

#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR

Move* creatMaillon(int joueur, char position[3]);
Move* insTT(Move *L, Move *moves);

#endif

// ----------------------------------------------------------------------------------------------