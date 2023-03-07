#include "moteur.h"

typedef struct move {
    int x; // position horizontale
    int y; // position vertical
    char joueur[6]; // joueur qui a joué le coup (blanc ou noir)
    struct move *suiv;
} Move;

Move *initAction(){
    Move *moves;
    moves=(Move*)malloc(sizeof(Move));
    if(moves == NULL){
        printf("\nAllocation impossible");
    }
    else {
        printf ("\nJoueur qui a joué le coup (blanc ou noir):");
        scanf ("%s", moves->joueur);
        printf ("\nPosition horizontale du joueur:");
        scanf ("%d",&moves->x);
        printf ("\nPosition verticale du joueur:");
        scanf ("%d",&moves->y);
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
        printf("%s a joué en (%d,%d)\n", L->joueur, L->x, L->y);
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