#include "moteur.h"


/// partie du code de Manon

void respectRegles(){
    char rep[3];
    char *listpos[10]; //tableau regroupant toutes les positions des pions 
    int pre = 0; // présent dan sla liste
    printf("Ou souhaitez-vous placer votre pion ?\n");
    scanf("%s", rep);
    while(strlen(rep)!=2){
        printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
        scanf("%s", rep);
    }
    printf("%ld\n", strlen(listpos));
    if((rep[0]>=97 && rep[0]<=104) && (rep[1]>=49 && rep[1]<=56)){
        printf("OK\n");
        for(int i=0; i <= strlen(listpos); i++){
            printf("%s", listpos[i]);
            if(listpos[i]==rep){
                printf("yey\n");
                pre = 1;
            }
        }
        if(pre == 1){
            printf("Position impossible car la case est déjà occupée\n");
        }
        else{
            printf("OK !\n");
            listpos[strlen(listpos)]=rep;
        }
    }
    else{
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }
}


int main(){
    respectRegles();
    return 0;
}





/// partie Latifa


Move *initAction(){
    Move *moves;
    moves=(Move*)malloc(sizeof(Move));
    if(moves == NULL){
        printf("\nAllocation impossible");
    }
    else {
        printf ("\nJoueur qui a joué le coup (blanc ou noir):");
        scanf ("%s", moves->joueur);
        printf ("\nPosition du joueur:");
        scanf ("%d",&moves->posi);
        moves->suiv=NULL;
    }
    return moves;
}

Move *insTT(Move *L, Move *moves){
    if(L==NULL) L=moves;
    else{
        moves->suiv=L;
        L=moves;
    }
    return L;
}

void printMoveHistory(Move *L){
    int cpt=0;
    while (L!=NULL){
        printf("%s a joué en (%d,%d)\n", L->joueur, L->posi);
        cpt++;
        L=L->suiv;
    }
    if (cpt==0) printf("\nListe vide!");
}

int main(){
    Move *L, *moves;
    L=NULL;
    while(1){
        moves=initAction();
        if(moves!=NULL){
            L=insTT(L,moves);
            printMoveHistory(L);
        }
    }
    return 0;
}