#include "IA.h"



char* demandeIA(char* rep, parametres* jeu)
{
    miniMax((2*jeu->lvlOrdi)-1);

    return rep;
}


void miniMax(int itera)
{
    Estimation* estimation = malloc(sizeof(Estimation));

    Move* noeud = deplacFin(estimation);
    char rep[3];

    if (itera > 0)
    {
        for (int i=1; i<=8; i++)
        {
            for (int j=1; j<=8; j++)
            {
                rep[0] = i+96;
                rep[1] = j+48;



                if (verifAllie(rep) != NULL)
                {
                    Evaluation();
                }
            }
        }
        miniMax(itera-1);
    }
}

int Evaluation(void)
{
    srand(time(NULL));
    return rand()%100;
}