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
// - prototypes des fonctions -------------------------------------------------------------------

#ifndef H_PA_PROTO_IA
#define H_PA_PROTO_IA



#endif

// ----------------------------------------------------------------------------------------------