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

typedef struct paramJeu
{
    int nbJoueurs;
    int lvlOrdi;
    int tourJoueur;
    int numTour;

} parametres;
extern parametres* jeu;
extern SDL_mutex* mutexJ;

typedef struct ordre {
    int action;
    char position[3];
    int error;
}Ordre;

extern Ordre *input;
extern SDL_mutex* mutexI;