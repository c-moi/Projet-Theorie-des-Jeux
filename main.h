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
// - import des fonctions de l'interface --------------------------------------------------------

#ifndef H_PA_INTERFACE
#define H_PA_INTERFACE

// #include "interface/interface.h"

#endif





// ----------------------------------------------------------------------------------------------
// - import des fonctions d'events --------------------------------------------------------------

#ifndef H_PA_MOTEUR
#define H_PA_MOTEUR 

#include "moteur/moteur.h"

#endif

// ----------------------------------------------------------------------------------------------