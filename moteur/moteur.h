// ----------------------------------------------------------------------------------------------
// - elements necessaires au bon fonctionnement du programme en general -------------------------

#ifndef H_PA_MAIN
#define H_PA_MAIN

#include "../globals.h"

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes moteur de jeu -------------------------------------------------------------------

#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR

typedef struct paramJeu
{
    int nbJoueurs;
    int lvlOrdi;
    int tourJoueur;

} parametres;

int moteurJeu(void* DATA);
void initPlto(Move** LN, Move** LB);

Move* creatMaillon(int joueur, char position[3]);
Move* insTT(Move *L, Move *moves);
Move* deplacFin(Move *L);

void respectRegles(Move** historique, Move** actuelG, Move** actuelH, Move* Maillon, Move* List_J1, Move* List_J2, parametres *jeu);
void verifContour(char rep[3],Move *LG, Move *List_J1, Move *List_J2, int pre);
void verifSuite(char rec[3], char rep[3], Move *Liste, int pre);

void deplacArriere(Move** actuelG, Move** actuelH, Move* histoCp);
void deplacAvant(Move** actuelG, Move** actuelH, Move* histoCp);
int estDans(char pion[3], Move *L); 
void printMoveHistory(Move *Liste, Move *End);
Move* supprimCoupApres(Move *actuel);

void retournPions(char pionallie[3], char rep[3], char tour[3], Move *LG, Move *L1, Move *L2);
Move* supprimerElement(Move* list, char valeur[3]);


#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import des fonctions de joueur -------------------------------------------------------------

#include "../joueur/joueur.h"

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import pour la gestion des fichiers --------------------------------------------------------

#include "../fichier/fichier.h"

// ----------------------------------------------------------------------------------------------