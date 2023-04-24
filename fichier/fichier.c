#include "fichier.h"


Move *chargerHistorique(Move* Liste)
{
    FILE *fichier;
    char ligne[10];
    int joueur;
    char position[3];
    fichier = fopen("historique.bin", "rb");

    if (fichier != NULL)
    {
        while (fgets(ligne, 10, fichier) != NULL)
        {
            sscanf(ligne, "%d;%s", &joueur, position);
            Move *moves = creatMaillon(joueur, position);
            Liste = insTT(Liste, moves);
        }
    }
    fclose(fichier);
    return Liste;
}

void sauvegarderHistorique (Move *L, Move *actuel)
{
    FILE *fichier;
    fichier = fopen("historique.bin", "wb");
    if (fichier != NULL)
    {
        while (L != actuel)
        {
            fprintf(fichier, "%d;%s\n", L->joueur, L->position);
            L=L->suiv;
        }
        fprintf(fichier, "%d;%s\n", L->joueur, L->position);
    }
    fclose(fichier);
}