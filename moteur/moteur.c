#include "moteur.h"


/// partie du code de Manon

// void respectRegles(){
//     char rep[3];
//     char *listpos[10]; //tableau regroupant toutes les positions des pions 
//     int pre = 0; // présent dan sla liste
//     printf("Ou souhaitez-vous placer votre pion ?\n");
//     scanf("%s", rep);
//     while(strlen(rep)!=2){
//         printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
//         scanf("%s", rep);
//     }
//     printf("%ld\n", strlen(listpos));
//     if((rep[0]>=97 && rep[0]<=104) && (rep[1]>=49 && rep[1]<=56)){
//         printf("OK\n");
//         for(int i=0; i <= strlen(listpos); i++){
//             printf("%s", listpos[i]);
//             if(listpos[i]==rep){
//                 printf("yey\n");
//                 pre = 1;
//             }
//         }
//         if(pre == 1){
//             printf("Position impossible car la case est déjà occupée\n");
//         }
//         else{
//             printf("OK !\n");
//             listpos[strlen(listpos)]=rep;
//         }
//     }
//     else{
//         printf("Ceci ne correspond pas à une case du plateau !\n");
//     }
// }


// int main(){
//     respectRegles();
//     return 0;
// }





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
    while(L->suiv != NULL){
            L=L->suiv;
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

void printMoveHistory(Move *L, Move *actuel){
    int cpt=0;
    if (actuel==NULL) printf("\nListe vide!");
    else if (actuel!=NULL){
        while (L!=actuel){
            printf("Mouvement %d : %d a joué en (%s)\n", cpt+1, L->joueur, L->position);
            L=L->suiv;
            cpt++;
        }
        printf("Mouvement %d : %d a joué en (%s)\n", cpt+1, L->joueur, L->position);
        cpt++;
    }
}

Move *deplacArriere(Move *actuel){
    if (actuel!=NULL){
        if(actuel->prec!=NULL){
            actuel=actuel->prec;
        }
        else if (actuel->prec==NULL){
            actuel=NULL;
        }
    }
    return actuel;
}

Move *deplacAvant(Move *actuel, Move *L){
    if (actuel!=NULL){
        if(actuel->suiv!=NULL){
            actuel=actuel->suiv;
        }
    }
    if(actuel==NULL){
        actuel=L;
    }
    return actuel;
}

void supprimCoupApres(Move *actuel){
    if (actuel!=NULL){
        Move *suivant=actuel->suiv;
        while(suivant!=NULL){
            actuel->suiv=suivant->suiv;
            if (actuel->suiv != NULL) {
                actuel->suiv->prec = actuel;
            }
            free(suivant);
            suivant = actuel->suiv;
        }
    }
}

// int main(){
//     Move *L, *moves, *actuel;
//     int choix=0 , var1=0;
//     char var2[3];
//     L=NULL;
//     actuel=NULL;
//     while (choix != 5){
//         printf("\nMenu :\n");
//         printf("1. Ajouter un coup joué\n");
//         printf("2. Se déplacer vers le coup précédent\n");
//         printf("3. Se déplacer vers l'avant\n");
//         printf("4. Afficher l'historique des coups joués\n");
//         printf("5. Quitter\n");
//         printf("Choix : ");
//         scanf("%d", &choix);
//         printf("\n");

//         switch (choix){
//             case 1:
//                 if (actuel!=NULL){
//                     if(actuel->suiv!=NULL){
//                         supprimCoupApres (actuel);
//                     }
//                     printf("\nJoueur (1 pour noir ou 2 pour blanc):");
//                     scanf("%d", &var1);
//                     printf("\nQuel est la position du joueur ?:");
//                     scanf("%s", var2);
//                     moves=initAction(var1, var2);
//                     L = insTT(L, moves);
//                     actuel = moves;
//                 }
//                 else if (actuel==NULL){
//                     if(L==NULL){
//                         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
//                         scanf("%d", &var1);
//                         printf("\nQuel est la position du joueur ?:");
//                         scanf("%s", var2);
//                         moves=initAction(var1, var2);
//                         L = insTT(L, moves);
//                         actuel = moves;
//                     }
//                     else if (L!=NULL){
//                         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
//                         scanf("%d", &var1);
//                         printf("\nQuel est la position du joueur ?:");
//                         scanf("%s", var2);
//                         moves=initAction(var1, var2);
//                         actuel=moves;
//                         moves->suiv=L;
//                         L=moves;
//                         moves->suiv->prec=moves;
//                         supprimCoupApres(actuel);
//                     }
//                 }
//                 break;
//             case 2:
//                 actuel=deplacArriere(actuel);
//                 if (actuel!=NULL) printf("Voici le coup précédent : %s", actuel->position);
//                 else{
//                     printf("Liste vide!\n");
//                 }
//                 break;
//             case 3:
//                 actuel=deplacAvant(actuel,L);
//                 if (actuel!=NULL) printf("Vous êtes revenu au coup : %s\n", actuel->position);
//                 else{
//                     printf("Vous êtes à votre dernier coup!\n");
//                 }
//                 break;
//             case 4:
//                 printMoveHistory(L,actuel);
//                 break;
//             case 5:
//                 printf("Au revoir !\n");
//                 break;
//             default:
//                 printf("Choix invalide, veuillez entrer une option valide.\n");
//         }
//     }
//     return 0;
// }