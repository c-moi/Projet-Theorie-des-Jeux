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
void initPlto();

Move* creatMaillon(int joueur, char position[3]);
Move* insTT(Move *L, Move *moves);
Move* deplacFin(Move *L);

void respectRegles(Move** historique, Move** actuelG, Move** actuelH, Move* Maillon, parametres *jeu);
Move* verifContour(char rep[3], parametres* jeu);
Move* verifAllie(char rep[3], parametres* jeu);

void deplacArriere(Move** actuelG, Move** actuelH, Move* histoCp);
void deplacAvant(Move** actuelG, Move** actuelH, Move* histoCp);
Move* estDans(char pion[3], Move *L);
void printMoveHistory(Move *Liste, Move *End);
Move* supprimCoupApres(Move *actuel);

void retournPions(Move *a_retorner);
//void retourArriere(Move *a_retourner);

void AfficheListe(const Move *l);
#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import pour la gestion des fichiers --------------------------------------------------------

#include "../fichier/fichier.h"

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import des fonctions de joueur -------------------------------------------------------------

#include "../joueur/joueur.h"

// ----------------------------------------------------------------------------------------------