// ----------------------------------------------------------------------------------------------
// - elements necessaires au bon fonctionnement du programme en general -------------------------

#ifndef H_PA_MAIN
#define H_PA_MAIN

#include "../globals.h"

#endif

// ----------------------------------------------------------------------------------------------
// - import du moteur ---------------------------------------------------------------------------





// ----------------------------------------------------------------------------------------------
// - import des fonctions de gestion de threads -------------------------------------------------
#ifndef H_PA_INTERFACE
#define H_PA_INTERFACE

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>






typedef struct listes {
    Move *new;
    Move *affiche;
} A_Comparer;

void Display(void);
void transDonne(char input[3], int *outputX, int *outputY);
char* transCoord( int inputX, int inputY);

int debug(void* DATA);
bool listCmp (Move* liste_printed);
Move* listCpy (void);

void affichQua (void);
Move *initAction();
void rempQua (void);
void rempTab (Move* liste);
void rempTab2 (Move* liste, char* val[8][8]);
void setupTab(char* val[8][8]);

#endif

// ----------------------------------------------------------------------------------------------