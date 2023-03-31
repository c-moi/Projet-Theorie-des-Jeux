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
//     if (actuel==NULL) printf("\nLGste vide!");
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

void respectRegles(char rep[3], Move *LG, Move *L){
    // L la liste historique
    LG=(Move *)malloc(sizeof (Move));//LG la Liste contenant tt les positions
    configPlayers(LG, rep);
    Move *List_J1 =NULL;// List_J1 la LGste contenant les positions des pions noirs
    Move *List_J2 =NULL;//List_J2 la LGste contenant les positions des pions blancs 
    Move *depl=NULL;
    Move *ptr1=LG;
    Move *moves1=creatMaillon(1,"e4");
    Move *moves2=creatMaillon(1,"d5");
    Move *moves3=creatMaillon(2,"e5");
    Move *moves4=creatMaillon(2,"d4");
    LG=insTT(LG,moves1);
    LG=insTT(LG,moves2);
    LG=insTT(LG,moves3);
    LG=insTT(LG,moves4);
    List_J1=insTT(List_J1,moves1);
    List_J1=insTT(List_J1,moves2);
    List_J2=insTT(List_J2,moves3);
    List_J2=insTT(List_J2,moves4);
    if(ptr1!=NULL){
        depl=depFin(depl);
        //L=depl->suiv;
    }    
   // char couleur[6];
    Move *move=(Move *)malloc(sizeof (Move));
    configPlayers(move, rep);
    int pre = 0; // présent dans la liste

    for(int j=0; j<=60; j++)
    {
        while(strlen(rep) != 2)
        {
            printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
            configPlayers(LG, rep);
        }

        if((rep[0] >= 97 && rep[0] <= 104) && (rep[1] >= 49 && rep[1] <= 56))
        {
            printf("OK\n");
            
            while(LG->suiv!=NULL)
            {
                if(LG->position == rep)
            while(move->suiv!=NULL)
            {
                if(move->position == rep)
                {
                    pre = 1;
                }
                LG = LG->suiv;
            }
            if(pre == 1){
                printf("Position impossible car la case est déjà occupée\n");
            }
            else{
                printf("La case est vide\n");
                // fonction qui fait le tour de rep
<<<<<< Manon
                verifContour(rep,LG,List_J1,List_J2,pre);
=======
                verifContour(rep);
>>>>>> Latifa
                //L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
            }
        }
        else{
            printf("Ceci ne correspond pas à une case du plateau !\n");
        }
<<<<<< Manon
        if(LG->joueur==1){
            Move *move=creatMaillon(1, rep);
            insTT(List_J1, move);
        }
        else{
           Move *move=creatMaillon(2, rep);
            insTT(List_J2, move); 
        }
        //LG->joueur = (LG->joueur % 2) + 1;  A mettre à la fin de la dernière règle
    }
}

void verifContour(char rep[3],Move *LG, Move *List_J1, Move *List_J2, int pre){
    int i=1;
    int j=0;
    char rec[3];
    rec[0]=rep[0]-1;
    if(LG->joueur==1){
        while(j<3)
        {
            for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
            {
                if(strcmp(rec,List_J2->position)==0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J1,pre);
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
                if(strcmp(rec, List_J2->position)==0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J1,pre);
                    i=0;
                }
                else
                {
                    i++;
                }
=======
        move->joueur = (move->joueur % 2) + 1;
    }
}

void verifContour(char rep[3]){
    int i=0;
    int j=0;
    char rec[3];
    rec[0]=rep[0]-1;

    while(j<3)
    {
        for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
        {
            if(strcmp(rec,"adverse")==0)
            {
                printf("Emplacement possible\n");
                i=0;
            }
            else
            {
                i++;
>>>>>> Latifa
            }
            j++;
            rec[0]=rep[0]+1;
            for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
            {
                if(strcmp(rec, List_J2->position))
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J1,pre);
                    i=0;
                }
                else
                {
                    i++;
                }
            }
            j++;
        }
<<<<<< Manon
    } 
    else{
       while(j<3)
        {
            for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
            {
                if(strcmp(rec,List_J1->position)==0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J2,pre);
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
                if(strcmp(rec, List_J1->position)==0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J2,pre);
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
                if(strcmp(rec, List_J1->position))
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec,rep,List_J2,pre);
                    i=0;
                }
                else
                {
                    i++;
                }
            }
            j++;
        } 
    }    
    if(i!=0)
    {
        printf("Emplacement impossible car aucun pion adverse autour\n");
        //break;
    }
}


void verifSuite(char rec[3], char rep[3], Move *Liste, int pre){
    char recl[3];
    recl[1]=rec[1];
    if(rec[0]==(rep[0]+1) && rec[1]==(rep[1])){
        for(int i=1;i<8;i++){
            recl[0]=rec[0]+i;
            if(pre==0){
                printf("position impossible");
                break;
            }
            else{
                //faire tt la ligne
            }
        }
=======
        j++;
        rec[0]=rep[0];
        for((rec[1])=((rep[1])-1); (rec[1])=((rep[1])+1); (rec[1])++)
        {
            if(strcmp(rec, "adverse"))
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
            if(strcmp(rec, "adverse"))
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
>>>>>> Latifa
    }
}


// void moteur (){
    
//     // Partie historique Latifa

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

<<<<<< Manon
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
//                     moves=creatMaillon(var1, var2);
//                     L = insTT(L, moves);
//                     actuel = moves;
//                 }
//                 else if (actuel==NULL){
//                     if(L==NULL){
//                         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
//                         scanf("%d", &var1);
//                         printf("\nQuel est la position du joueur ?:");
//                         scanf("%s", var2);
//                         moves=creatMaillon(var1, var2);
//                         L = insTT(L, moves);
//                         actuel = moves;
//                     }
//                     else if (L!=NULL){
//                         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
//                         scanf("%d", &var1);
//                         printf("\nQuel est la position du joueur ?:");
//                         scanf("%s", var2);
//                         moves=creatMaillon(var1, var2);
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
// }




=======
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

Move *chargerHistorique() {
    Move *L = NULL;
    FILE *fichier;
    char ligne[10];
    int joueur;
    char position[3];
    fichier = fopen("historique.bi", "rb");
    if (fichier != NULL) {
        while (fgets(ligne, 10, fichier) != NULL) {
            sscanf(ligne, "%d;%s", &joueur, position);
            Move *moves = creatMaillon(joueur, position);
            L = insTT(L, moves);
        }
    }
    fclose(fichier);
    return L;
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
>>>>>> Latifa
