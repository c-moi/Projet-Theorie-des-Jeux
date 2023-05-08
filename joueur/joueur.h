// ----------------------------------------------------------------------------------------------
// - elements necessaires au bon fonctionnement du programme en general -------------------------

#ifndef H_PA_MAIN
#define H_PA_MAIN

#include "../globals.h"

#endif

// ----------------------------------------------------------------------------------------------




// ----------------------------------------------------------------------------------------------
// - import du moteur ---------------------------------------------------------------------------

#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR

typedef struct paramJeu
{
    int nbJoueurs;
    int lvlOrdi;
    int tourJoueur;

} parametres;
void viderBuffer(void);

Move *creatMaillon(int joueur, char position[3]);
#endif


// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes configuration du/des joueurs ----------------------------------------------------

#ifndef H_PA_JOUEUR
#define H_PA_JOUEUR

parametres configPlayers(parametres jeu);

Move* tourJoueur(parametres* jeu);
char* demandeJoueur(char* rep);

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import algorithme de l'IA ------------------------------------------------------------------

#include "../IA/IA.h"

// ----------------------------------------------------------------------------------------------