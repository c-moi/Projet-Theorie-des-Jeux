#include "moteur.h"


/// partie du code de Manon

void respectRegles(char rep[3]){
    char couleur[6];
    Move *move=(Move *)malloc(sizeof (Move));
    configPlayers(move, rep);
    //L la liste contenant tt les positions
    // L1 la liste de Latifa contenant les positions des pions noirs
    //L2 la liste contenant les positions des pions blancs 
    int pre = 0; // présent dans la liste

    for(int j=0;j<=60;j++){
        while(strlen(rep)!=2){
            printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
            configPlayers(move, rep);
        }
        if((rep[0]>=97 && rep[0]<=104) && (rep[1]>=49 && rep[1]<=56)){
            printf("OK\n");
            while(move->suiv!=NULL){
                if(move->posi==rep){
                    pre = 1;
                }
                move = move->suiv;
            }
            if(pre == 1){
                printf("Position impossible car la case est déjà occupée\n");
            }
            else{
                printf("La case est vide\n");
                // fonction qui fait le tour de rep
                tour(rep);
                //L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
            }
        }
        else{
            printf("Ceci ne correspond pas à une case du plateau !\n");
        }
        move->joueur = (move->joueur%2)+1;
    }
}

void tour(char rep[3]){
    int i=0;
    int j=0;
    char rec[3];
    rec[0]=rep[0]-1;
    while(j<3){
        for(rec[1]=rep[1]-1;rec[1]=rep[1]+1;rec[1]++){
            if(rec=="adverse"){
                printf("Emplacement possible\n");
                i=0;
            }
            else{
                i++;
            }
        }
        j++;
        rec[0]=rep[0];
        for(rec[1]=rep[1]-1;rec[1]=rep[1]+1;rec[1]++){
            if(rec=="adverse"){
                printf("Emplacement possible\n");
                i=0;
            }
            else{
                i++;
            }
        }
        j++;
        rec[0]=rep[0]+1;
        for(rec[1]=rep[1]-1;rec[1]=rep[1]+1;rec[1]++){
            if(rec=="adverse"){
                printf("Emplacement possible\n");
                i=0;
            }
            else{
                i++;
            }
        }
        j++;
    }
    if(i!=0){
        printf("Emplacement impossible car aucun pion adverse autour\n");
    }
    else{
        printf("Règle suivante\n");
    }
}




/// partie Latifa

// Move *initAction(){
//     Move *moves;
//     moves=(Move*)malloc(sizeof(Move));
//     if(moves == NULL){
//         printf("\nAllocation impossible");
//     }
//     else {
//         printf ("\nJoueur qui a joué le coup (blanc ou noir):");
//         scanf ("%s", moves->joueur);
//         printf ("\nPosition horizontale du joueur:");
//         scanf ("%d",&moves->x);
//         printf ("\nPosition verticale du joueur:");
//         scanf ("%d",&moves->y);
//         moves->suiv=NULL;
//     }
//     return moves;
// }

// Move *insTT(Move *L, Move *moves){
//     if(L==NULL) L=moves;
//     else{
//         moves->suiv=L;
//         L=moves;
//     }
//     return L;
// }

// void printMoveHistory(Move *L){
//     int cpt=0;
//     while (L!=NULL){
//         printf("%s a joué en (%d,%d)\n", L->joueur, L->x, L->y);
//         cpt++;
//         L=L->suiv;
//     }
//     if (cpt==0) printf("\nListe vide!");
// }

// int main(){
//     Move *L, *moves;
//     L=NULL;
//     while(1){
//         moves=initAction();
//         if(moves!=NULL){
//             L=insTT(L,moves);
//             printMoveHistory(L);
//         }
//     }
//     return 0;
// }