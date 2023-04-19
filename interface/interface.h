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
// - import du moteur ---------------------------------------------------------------------------
//#include "moteur/moteur.c"




// ----------------------------------------------------------------------------------------------
// - import des fonctions de gestion de threads -------------------------------------------------
#ifndef H_PA_INTERFACE
#define H_PA_INTERFACE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

int Display (void* liste);

void affichQua (void);
Move *initAction();
void rempQua (void);
Move * rempTab2 (char val[8][8]);
void rempTab (void);

#endif

// ----------------------------------------------------------------------------------------------






// ----------------------------------------------------------------------------------------------
// - import de l'interface ----------------------------------------------------------------------

#ifndef H_PA_PROTO_INTERFACE
#define H_PA_PROTO_INTERFACE



#endif

// ----------------------------------------------------------------------------------------------