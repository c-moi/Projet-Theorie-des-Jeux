#include "main.h"
         


int main(int argc, char **argv)
{
    Move* lst_pions = NULL;


    SDL_Thread* Thread = SDL_CreateThread(Display, "Affichage", lst_pions);

    moteurJeu(lst_pions);
    


    SDL_WaitThread(Thread, NULL);

    return 0;

}