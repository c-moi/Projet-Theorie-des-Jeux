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

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - prototypes des fonctions -------------------------------------------------------------------

#ifndef H_PA_IA
#define H_PA_IA

char* demandeIA(char* rep, parametres* jeu);

#endif

// ----------------------------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import pour la gestion des fichiers --------------------------------------------------------

#ifndef H_PA_FICHIERS
#define H_PA_FICHIERS

#include "../fichier/fichier.h"

#endif

// ----------------------------------------------------------------------------------------------