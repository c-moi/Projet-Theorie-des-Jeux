#include "fichier.h"

void chargerHistorique(Move** liste, Move** actuelG, Move** histo, Move** actuelH, int* fin)
{
    FILE *fichier=NULL;
    int joueur;
    char position[3];
    Move* moves=NULL;
    Move* dernierCoup=NULL;
    fichier = fopen("fichier/historique.bin", "rb");
    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END);
        long int tailleFichier = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);

        while (ftell(fichier) < tailleFichier)
        {
            fread(&joueur, sizeof(int), 1, fichier);
            fread(position, sizeof(char), 3 , fichier);

            *histo = insTT(*histo, creatMaillon(joueur, position));
            *actuelH = deplacFin(*histo);
            
            *liste = insTT(*liste, creatMaillon(joueur, position));
            *actuelG = deplacFin(*liste);
            (*fin)++;
        }
    }
    fclose(fichier);
}

void sauvegarderHistorique (Move *L, Move *actuel)
{
    FILE *fichier;
    fichier = fopen("fichier/historique.bin", "wb");
    if (fichier != NULL)
    {
        if (L != NULL && actuel != NULL)
        {
            while (L != actuel)
            {
                fwrite(&(L->joueur),sizeof(int), 1, fichier);
                fwrite(L->position,sizeof(char), 3, fichier);
                L=L->suiv;
            }
            fwrite(&(L->joueur),sizeof(int), 1, fichier);
            fwrite(L->position,sizeof(char), 3, fichier);
        }
        else 
        {
            printf("Une des liste est nulle!\n");
        }
    }
    fclose(fichier);
}