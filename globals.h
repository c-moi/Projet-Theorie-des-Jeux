#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <unistd.h>

typedef struct move {
    char position[3]; 
    int joueur; // joueur qui a joué le coup (1 jeton noir ou 2 jeton blanc)

    struct move *switched; // liste des pions retournés par le coup

    struct move *suiv;
    struct move *prec;
} Move;

extern Move* listeG;
extern SDL_mutex* mutexG;
