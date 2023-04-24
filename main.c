#include "main.h"

Move* listeG = NULL;
SDL_mutex* mutexG = NULL;


int main(int argc, char **argv)
{
    // initialisatio du mutex
    mutexG = SDL_CreateMutex();

    SDL_Thread* MoteurJeu = SDL_CreateThread(moteurJeu, "moteurJeu", NULL);

    Display();



    // SDL_Thread* Display = SDL_CreateThread(Display, "Affichage", lst_pions);

    // moteurJeu(lst_pions);
    


    SDL_WaitThread(MoteurJeu, NULL);

    return 0;

}