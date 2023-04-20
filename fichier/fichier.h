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



#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR

typedef struct paramJeu
{
    int nbJoueurs;
    int lvlOrdi;
    int tourJoueur;

} parametres;

int moteurJeu(void *liste);
Move* initPlto(Move* liste, Move* LN, Move* LB);

Move* creatMaillon(int joueur, char position[3]);
Move* insTT(Move *L, Move *moves);
Move* deplacFin(Move *L);

Move* respectRegles(Move* Liste, Move* Maillon, Move* List_J1, Move* List_J2, parametres *jeu);
void verifContour(char rep[3],Move *LG, Move *List_J1, Move *List_J2, int pre, parametres *jeu);
void verifAllie(char rec[3], char rep[3], Move *Liste, Move *LN, Move *LB, int pre, parametres *jeu);

Move *deplacArriere(Move *actuel);
Move *deplacAvant(Move *actuel);
void printMoveHistory(Move *L, Move *actuel);
void supprimCoupApres(Move *actuel);

Move *listAdverse(Move *liste, Move *List_J1, Move *List_J2);
void retournPions(char *suite[3],  Move *Liste, Move *L1, Move *L2);
int estDans(char pion[3], Move *L);
Move* supprimerElement(Move* list, char valeur[3]);


#endif




// ----------------------------------------------------------------------------------------------
// - prototypes gestion des fichiers ------------------------------------------------------------

#ifndef H_PA_FICHIER
#define H_PA_FICHIER

Move *chargerHistorique(Move* Liste);
void sauvegarderHistorique (Move *L, Move *actuel);


#endif

// ----------------------------------------------------------------------------------------------