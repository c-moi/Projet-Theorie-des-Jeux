#include "fichier.h"

void sauvegarderHistorique (Move *L, Move *actuel){
    FILE *fichier;
    fichier = fopen("historique.bi", "wb");
    if (fichier!=NULL){
        while (L!=actuel){
            fprintf(fichier, "%d;%s", L->joueur, L->position);
            L=L->suiv;
        }
        fprintf(fichier, "%d;%s", L->joueur, L->position);
    }
    fclose(fichier);
}