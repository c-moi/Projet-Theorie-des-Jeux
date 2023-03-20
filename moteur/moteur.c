#include "moteur.h"

/// partie Latifa

Move *creatMaillon(int joueur, char position[3]){
    Move *moves;
    moves=(Move*)malloc(sizeof(Move));
    if(moves == NULL){
        printf("\nAllocation impossible");
    }
    else {
        moves->joueur=joueur;
        strcpy(moves->position, position);
        moves->prec=NULL;
        moves->suiv=NULL;
    }
    return moves;
}

Move *depFin(Move *L){
    if(L!=NULL)
    {
        while(L->suiv != NULL){
                L=L->suiv;
        }
    }
    return L;
}

Move *insTT(Move *L, Move *moves){
    Move *dep=L;
    if (L==NULL){
        L=moves;
        L->prec=NULL;
        L->suiv=NULL;
    }
    else{
        dep = depFin(dep);
        moves->suiv=dep->suiv;
        moves->prec=dep;
        dep->suiv=moves;
    }
    return L;
}

// void printMoveHistory(Move *L, Move *actuel){
//     int cpt=0;
//     if (actuel==NULL) printf("\nListe vide!");
//     else if (actuel!=NULL){
//         while (L!=actuel){
//             printf("Mouvement %d : %d a joué en (%s)\n", cpt+1, L->joueur, L->position);
//             L=L->suiv;
//             cpt++;
//         }
//         printf("Mouvement %d : %d a joué en (%s)\n", cpt+1, L->joueur, L->position);
//         cpt++;
//     }
// }

// Move *deplacArriere(Move *actuel){
//     if (actuel!=NULL){
//         if(actuel->prec!=NULL){
//             actuel=actuel->prec;
//         }
//         else if (actuel->prec==NULL){
//             actuel=NULL;
//         }
//     }
//     return actuel;
// }

// Move *deplacAvant(Move *actuel, Move *L){
//     if (actuel!=NULL){
//         if(actuel->suiv!=NULL){
//             actuel=actuel->suiv;
//         }
//     }
//     if(actuel==NULL){
//         actuel=L;
//     }
//     return actuel;
// }

// void supprimCoupApres(Move *actuel){
//     if (actuel!=NULL){
//         Move *suivant=actuel->suiv;
//         while(suivant!=NULL){
//             actuel->suiv=suivant->suiv;
//             if (actuel->suiv != NULL) {
//                 actuel->suiv->prec = actuel;
//             }
//             free(suivant);
//             suivant = actuel->suiv;
//         }
//     }
// }




/// partie du code de Manon

void respectRegles(char rep[3]){
    Move *Li=(Move *)malloc(sizeof (Move));//Li la liste contenant tt les positions
    configPlayers(Li, rep);
   // Move *L=NULL;
    Move *L1 =NULL;// L1 la liste de Latifa contenant les positions des pions noirs
    Move *L2 =NULL;//L2 la liste contenant les positions des pions blancs 
    Move *depl=NULL;
    Move *ptr1=Li;
    Move *moves1=creatMaillon(1,"e4");
    Move *moves2=creatMaillon(1,"d5");
    Move *moves3=creatMaillon(2,"e5");
    Move *moves4=creatMaillon(2,"d4");
    Li=insTT(Li,moves1);
    Li=insTT(Li,moves2);
    Li=insTT(Li,moves3);
    Li=insTT(Li,moves4);
    L1=insTT(L1,moves1);
    L1=insTT(L1,moves2);
    L2=insTT(L2,moves3);
    L2=insTT(L2,moves4);
    if(ptr1!=NULL){
        depl=depFin(depl);
        Li=depl->suiv;
    }    

    
    int pre = 0; // présent dans la liste

    for(int j=0; j<=60; j++)
    {
        while(strlen(rep) != 2)
        {
            printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
            configPlayers(Li, rep);
        }

        if((rep[0] >= 97 && rep[0] <= 104) && (rep[1] >= 49 && rep[1] <= 56))
        {
            printf("OK\n");
            while(Li->suiv!=NULL)
            {
                if(Li->position == rep)
                {
                    pre = 1;
                }
                Li = Li->suiv;
            }
            if(pre == 1){
                printf("Position impossible car la case est déjà occupée\n");
            }
            else{
                printf("La case est vide\n");
                // fonction qui fait le tour de rep
                verifContour(rep,Li);
                //L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
            }
        }
        else{
            printf("Ceci ne correspond pas à une case du plateau !\n");
        }
        Li->joueur = (Li->joueur % 2) + 1;
    }
}

void verifContour(char rep[3],Move *Li){
    int i=0;
    int j=0;
    char rec[3];
    rec[0]=rep[0]-1;

    while(j<3)
    {
        for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
        {
            if(strcmp(rec,Li->position)==0)
            {
                printf("Emplacement possible\n");
                i=0;
            }
            else
            {
                i++;
            }
        }
        j++;
        rec[0]=rep[0];
        for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
        {
            if(strcmp(rec, Li->position)==0)
            {
                printf("Emplacement possible\n");
                i=0;
            }
            else
            {
                i++;
            }
        }
        j++;
        rec[0]=rep[0]+1;
        for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
        {
            if(strcmp(rec, Li->position))
            {
                printf("Emplacement possible\n");
                i=0;
            }
            else
            {
                i++;
            }
        }
        j++;
    }
    if(i!=0)
    {
        printf("Emplacement impossible car aucun pion adverse autour\n");
    }
    else
    {
        printf("Règle suivante\n");
    }
}




