#include "moteur.h"

void moteurJeu(Move *listeG)
{
    Move* maillon = NULL;
    // init historique coups
    Move *histoCp = NULL;
    // init pions noirs
    Move *List_J1 = NULL;
    // init pions blancs
    Move *List_J2 = NULL;

    // position dans l'historique
    Move *actuel = NULL;

    // choix action joueur
    int action;

    // initialisation des joueurs
    char* rep = malloc(sizeof(char) * 3);







    // initialisation du jeu
    listeG = initPlto(listeG, List_J1, List_J2);
    actuel = deplacFin(listeG);

    rep[3] = configPlayers(listeG, rep); // à modifier

    // En attendant :
    parametres jeu = {2, 0, 1};

    //Chargement de partie si souhaité
    char choix_reprendre;
    printf("Voulez-vous reprendre la partie sauvegardée ? (O/N) : ");
    scanf("%c", &choix_reprendre);
    if (choix_reprendre == 'O' || choix_reprendre == 'o')
    {
        histoCp = chargerHistorique(histoCp);
        actuel->suiv = histoCp;

        while (actuel->suiv != NULL)
        {
            actuel = actuel->suiv;
        }
        printf("Vous avez repris la partie depuis l'historique sauvegardé.\n");
    }
    else
    {
        printf("Nouvelle partie démarrée.\n");
    }

    // boucle de jeu
    while (action != 6)
    {
        // configuration action du joueur
        action = 0;

        rep = "";

        // demande à l'utilisateur ce qu'il veut faire
        printf("\n Menu :\n");
        printf("1. Jouer un coup \n");
        printf("2. Se déplacer vers le coup précédent \n");
        printf("3. Se déplacer vers l'avant \n");
        printf("4. Afficher l'historique des coups joués \n");
        printf("5. Sauvegarder la partie en cours\n");
        printf("6. Quitter \n");
        printf("Quel est votre choix : ");
        scanf("%d", &action);
        printf("\n");

        switch (action)
        {
            case 1:
                // il faut faire cette demande dans joueur.
                if (actuel != NULL)
                {
                    if (actuel->suiv != NULL)
                    {
                        supprimCoupApres(actuel);
                    }
                    while (strlen(rep) != 2)
                    {
                        printf("\nQuel est la position du joueur :");
                        scanf("%s", rep);
                    }
                    maillon = creatMaillon(jeu.tourJoueur, rep);
                    respectRegles(actuel, maillon); // à mettre dans respectRegles
                    actuel = maillon; // à mettre dans respectRegles
                }
                else if (actuel == NULL)
                {
                    if (histoCp == NULL)
                    {
                        while (strlen(rep) != 2)
                        {
                            printf("\nQuel est la position du joueur :");
                            scanf("%s", rep);
                        }
                        maillon = creatMaillon(jeu.tourJoueur, rep);
                        respectRegles(actuel, maillon); // à mettre dans respectRegles
                        actuel = maillon; // à mettre dans respectRegles
                    }
                    else if (histoCp != NULL)
                    {
                        while (strlen(rep) != 2)
                        {
                            printf("\nQuel est la position du joueur :");
                            scanf("%s", rep);
                        }
                        maillon = creatMaillon(jeu.tourJoueur, rep);
                        respectRegles(actuel, maillon); // à mettre dans respectRegles
                        actuel = maillon; // à mettre dans respectRegles
                        maillon->suiv = histoCp; // à mettre dans respectRegles
                        histoCp = maillon; // à mettre dans respectRegles
                        maillon->suiv->prec = maillon; // à mettre dans respectRegles
                        supprimCoupApres(actuel); // à mettre dans respectRegles
                    }
                }
                break;
            case 2:
                actuel = deplacArriere(actuel);
                break;
            case 3:
                actuel = deplacAvant(actuel);
                break;
            case 4:
                printMoveHistory(histoCp, actuel);
                break;
            case 5:
                sauvegarderHistorique(histoCp, actuel);
                break;
            case 6:
                printf("Au revoir ! \n");
                break;

            default:
                printf("Choix invalide, ceci n'est pas une action possible... \n");
                break;
        }
    }
}

Move *initPlto(Move *liste, Move *LN, Move *LB)
{
    liste = insTT(liste, creatMaillon(1, "d4"));
    liste = insTT(liste, creatMaillon(2, "e4"));
    liste = insTT(liste, creatMaillon(1, "d5"));
    liste = insTT(liste, creatMaillon(2, "e5"));

    return liste;
}

Move *creatMaillon(int joueur, char position[3])
{
    Move *moves;
    moves = (Move *)malloc(sizeof(Move));

    if (moves == NULL)
    {
        printf("\nAllocation impossible");
    }
    else
    {
        moves->joueur = joueur;
        strcpy(moves->position, position);
        moves->prec = NULL;
        moves->suiv = NULL;
    }
    return moves;
}

Move *insTT(Move *L, Move *moves)
{
    Move *dep = L;
    if (L == NULL)
    {
        L = moves;
        L->prec = NULL;
        L->suiv = NULL;
    }
    else
    {
        dep = deplacFin(dep);
        moves->suiv = dep->suiv;
        moves->prec = dep;
        dep->suiv = moves;
    }
    return L;
}

Move *deplacFin(Move *L)
{
    if (L != NULL)
    {
        while (L->suiv != NULL)
        {
            L = L->suiv;
        }
    }
    return L;
}

Move* respectRegles(Move* Liste, Move* Maillon)
{
    int pre = 0;
    if ((Maillon->position[0] >= 97 && Maillon->position[0] <= 104) && (Maillon->position[1] >= 49 && Maillon->position[1] <= 56))
    {
        while (Liste->suiv != NULL)
        {
            if (Liste->position == Maillon->position)
            {
                pre = 1;
            }
            Liste = Liste->suiv;
        }

        if (pre == 1)
        {
            printf("Position impossible car la case est déjà occupée\n");
        }
        else
        {
            // ###### A compléter ######

            // printf("La case est vide\n");
            // fonction qui fait le tour de rep
            // verifContour(rep, LG, List_J1, List_J2, pre);
            // L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
        }
    }
    else
    {
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }
    return Liste;
}

// Je vous laisserai modifier parce que je sais pas ce qui est la dernière version
void verifContour(char rep[3], Move *LG, Move *List_J1, Move *List_J2, int pre)
{
    int i = 1;
    int j = 0;
    char rec[3];
    rec[0] = rep[0] - 1;
    if (LG->joueur == 1)
    {
        while (j < 3)
        {
            for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
            {
                if (strcmp(rec, List_J2->position) == 0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec, rep, List_J1, pre);
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            j++;
            rec[0] = rep[0];
            for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
            {
                if (strcmp(rec, List_J2->position) == 0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec, rep, List_J1, pre);
                    i = 0;
                }
                else
                {
                    i++;
                }
                move->joueur = (move->joueur % 2) + 1;
            }
        }
    }
    else
    {
        while (j < 3)
        {
            for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
            {
                if (strcmp(rec, List_J1->position) == 0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec, rep, List_J2, pre);
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            j++;
            rec[0] = rep[0];
            for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
            {
                if (strcmp(rec, List_J1->position) == 0)
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec, rep, List_J2, pre);
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            j++;
            rec[0] = rep[0] + 1;
            for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
            {
                if (strcmp(rec, List_J1->position))
                {
                    printf("Emplacement possible\n");
                    verifSuite(rec, rep, List_J2, pre);
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            j++;
        }
    }
    if (i != 0)
    {
        printf("Emplacement impossible car aucun pion adverse autour\n");
    }
}

void verifSuite(char rec[3], char rep[3], Move *Liste, int pre)
{
    char recl[3];
    recl[1] = rec[1];

    if (rec[0] == (rep[0] + 1) && rec[1] == (rep[1]))
    {
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] + i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                //faire tt la ligne
            }
        }
    }
}

Move *deplacArriere(Move *actuel)
{
    if (actuel == NULL)
    {
        printf("Vous ne pouvez pas revenir en arrière, aucun coup n'a été joué au préalable !\n");
    }
    if (actuel != NULL)
    {
        if (actuel->prec != NULL)
        {
            actuel = actuel->prec;
            printf("Vous êtes revenu au coup : %s\n", actuel->position);
        }
        else
        {
            printf("Vous êtes au début du jeu !\n");
        }
    }
    return actuel;
}

Move *deplacAvant(Move *actuel)
{
    if (actuel == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (actuel != NULL)
    {
        if (actuel->suiv != NULL)
        {
            actuel = actuel->suiv;
            printf("Vous êtes revenu au coup : %s\n", actuel->position);
        }
        else
        {
            printf("Vous êtes à votre dernier coup!\n");
        }
    }
    return actuel;
}

void printMoveHistory(Move *Liste, Move *actuel)
{
    int cpt = 0;
    if (Liste == NULL)
        printf("\n Liste vide ! \n");

    else if (Liste != NULL)
    {
        while (Liste != actuel)
        {
            printf("Mouvement %d : %d a joué en (%s)\n", cpt + 1, Liste->joueur, Liste->position);
            Liste = Liste->suiv;
            cpt++;
        }
        printf("Mouvement %d : %d a joué en (%s)\n", cpt + 1, Liste->joueur, Liste->position);
    }
}

void supprimCoupApres(Move *actuel)
{
    if (actuel != NULL)
    {
        Move *suivant = actuel->suiv;
        while (suivant != NULL)
        {
            actuel->suiv = suivant->suiv;
            if (actuel->suiv != NULL)
            {
                actuel->suiv->prec = actuel;
            }
            free(suivant);
            suivant = actuel->suiv;
        }
    }
}
























/// partie Latifa

// Move *creatMaillon(int joueur, char position[3]){
//     Move *moves;
//     moves=(Move*)malloc(sizeof(Move));
//     if(moves == NULL){
//         printf("\nAllocation impossible");
//     }
//     else {
//         moves->joueur=joueur;
//         strcpy(moves->position, position);
//         moves->prec=NULL;
//         moves->suiv=NULL;
//     }
//     return moves;
// }

// Move *depFin(Move *L){
//     if(L!=NULL)
//     {
//         while(L->suiv != NULL){
//                 L=L->suiv;
//         }
//     }
//     return L;
// }

// Move* insTT(Move *L, Move *moves){
//     Move *dep=L;
//     if (L==NULL){
//         L=moves;
//         L->prec=NULL;
//         L->suiv=NULL;
//     }
//     else{
//         dep = depFin(dep);
//         moves->suiv=dep->suiv;
//         moves->prec=dep;
//         dep->suiv=moves;
//     }
//     return L;
// }

// void printMoveHistory(Move *L, Move *actuel){
//     int cpt=0;
//     if (actuel==NULL)
//         printf("\nLGste vide!");
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

// Move *deplacArriere(Move *actuel)
// {
//     if (actuel != NULL)
//     {
//         if (actuel->prec != NULL)
//         {
//             actuel = actuel->prec;
//         }
//         else if (actuel->prec == NULL)
//         {
//             actuel = NULL;
//         }
//     }
//     return actuel;
// }

// Move *deplacAvant(Move *actuel, Move *L)
// {
//     if (actuel != NULL)
//     {
//         if (actuel->suiv != NULL)
//         {
//             actuel = actuel->suiv;
//         }
//     }
//     if (actuel == NULL)
//     {
//         actuel = L;
//     }
//     return actuel;
// }

// void supprimCoupApres(Move *actuel)
// {
//     if (actuel != NULL)
//     {
//         Move *suivant = actuel->suiv;
//         while (suivant != NULL)
//         {
//             actuel->suiv = suivant->suiv;
//             if (actuel->suiv != NULL)
//             {
//                 actuel->suiv->prec = actuel;
//             }
//             free(suivant);
//             suivant = actuel->suiv;
//         }
//     }
// }


// / partie du code de Manon

// void respectRegles(char rep[3], Move *LG, Move *L)
// {
    // L la liste historique
    // (inutile, risque de conflit lors de l'attribution des valeurs)
    // LG=(Move *)malloc(sizeof (Move));//LG la Liste contenant tt les positions
    // configPlayers(LG, rep);
    // Move *List_J1 =NULL;// List_J1 la LGste contenant les positions des pions noirs
    // Move *List_J2 =NULL;//List_J2 la LGste contenant les positions des pions blancs
    // Move *depl=NULL;
    // Move *ptr1=LG;
    // Move *moves1=creatMaillon(1,"e4");
    // Move *moves2=creatMaillon(1,"d5");
    // Move *moves3=creatMaillon(2,"e5");
    // Move *moves4=creatMaillon(2,"d4");
    // LG=insTT(LG,moves1);
    // LG=insTT(LG,moves2);
    // LG=insTT(LG,moves3);
    // LG=insTT(LG,moves4);
    // List_J1 = insTT(List_J1, moves1); // à ajouter
    // List_J1 = insTT(List_J1, moves2); // à ajouter
    // List_J2 = insTT(List_J2, moves3); // à ajouter
    // List_J2 = insTT(List_J2, moves4); // à ajouter
    // if (ptr1 != NULL)
    // {
    //     depl = depFin(depl);
    //     // L=depl->suiv;
    // }
    // char couleur[6];
    // Move *move=(Move *)malloc(sizeof (Move));
    // configPlayers(move, rep);
    // int pre = 0; // présent dans la liste

    // for (int j = 0; j <= 60; j++)
    // {
        // while (strlen(rep) != 2)
        // {
        //     printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
        //     configPlayers(LG, rep);
        // }

        // if ((rep[0] >= 97 && rep[0] <= 104) && (rep[1] >= 49 && rep[1] <= 56))
        // {
        //     printf("OK\n");

        //     while (LG->suiv != NULL)
        //     {
        //         if (LG->position == rep)
        //         {
        //             pre = 1;
        //         }
        //         LG = LG->suiv;
        //     }
        //     if (pre == 1)
        //     {
        //         printf("Position impossible car la case est déjà occupée\n");
        //     }
        //     else
        //     {
        //         printf("La case est vide\n");
        //         // fonction qui fait le tour de rep
        //         verifContour(rep, LG, List_J1, List_J2, pre);
        //         // L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
        //     }
        // }
        // else
        // {
        //     printf("Ceci ne correspond pas à une case du plateau !\n");
        // }
        // if (LG->joueur == 1)
        // {
        //     Move *move = creatMaillon(1, rep);
        //     insTT(List_J1, move);
        // }
        // else
        // {
        //     Move *move = creatMaillon(2, rep);
        //     insTT(List_J2, move);
        // }
        // LG->joueur = (LG->joueur % 2) + 1;  A mettre à la fin de la dernière règle
//     }
// }


// // Je vous laisserai modifier parce que je sais pas ce qui est la dernière version
// void verifContour(char rep[3], Move *LG, Move *List_J1, Move *List_J2, int pre)
// {
//     int i = 1;
//     int j = 0;
//     char rec[3];
//     rec[0] = rep[0] - 1;
//     if (LG->joueur == 1)
//     {
//         while (j < 3)
//         {
//             for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
//             {
//                 if (strcmp(rec, List_J2->position) == 0)
//                 {
//                     printf("Emplacement possible\n");
//                     verifSuite(rec, rep, List_J1, pre);
//                     i = 0;
//                 }
//                 else
//                 {
//                     i++;
//                 }
//             }
//             j++;
//             rec[0] = rep[0];
//             for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
//             {
//                 if (strcmp(rec, List_J2->position) == 0)
//                 {
//                     printf("Emplacement possible\n");
//                     verifSuite(rec, rep, List_J1, pre);
//                     i = 0;
//                 }
//                 else
//                 {
//                     i++;
//                 }
//                 move->joueur = (move->joueur % 2) + 1;
//             }
//         }
//     }
//     else
//     {
//         while (j < 3)
//         {
//             for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
//             {
//                 if (strcmp(rec, List_J1->position) == 0)
//                 {
//                     printf("Emplacement possible\n");
//                     verifSuite(rec, rep, List_J2, pre);
//                     i = 0;
//                 }
//                 else
//                 {
//                     i++;
//                 }
//             }
//             j++;
//             rec[0] = rep[0];
//             for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
//             {
//                 if (strcmp(rec, List_J1->position) == 0)
//                 {
//                     printf("Emplacement possible\n");
//                     verifSuite(rec, rep, List_J2, pre);
//                     i = 0;
//                 }
//                 else
//                 {
//                     i++;
//                 }
//             }
//             j++;
//             rec[0] = rep[0] + 1;
//             for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
//             {
//                 if (strcmp(rec, List_J1->position))
//                 {
//                     printf("Emplacement possible\n");
//                     verifSuite(rec, rep, List_J2, pre);
//                     i = 0;
//                 }
//                 else
//                 {
//                     i++;
//                 }
//             }
//             j++;
//         }
//     }
//     if (i != 0)
//     {
//         printf("Emplacement impossible car aucun pion adverse autour\n");
//     }
// }

// void verifSuite(char rec[3], char rep[3], Move *Liste, int pre)
// {
//     char recl[3];
//     recl[1] = rec[1];

//     if (rec[0] == (rep[0] + 1) && rec[1] == (rep[1]))
//     {
//         for (int i = 1; i < 8; i++)
//         {
//             recl[0] = rec[0] + i;
//             if (pre == 0)
//             {
//                 printf("position impossible");
//                 break;
//             }
//             else
//             {
//                 //faire tt la ligne
//             }
//         }
//     }
// }

        // void moteur()
        // {

            // Partie historique Latifa

            // Move *L, *moves, *actuel;
            // int choix = 0, var1 = 0;
            // char var2[3];
            // L = NULL;
            // actuel = NULL;
            // while (choix != 5)
            // {
            //     printf("\nMenu :\n");
            //     printf("1. Ajouter un coup joué\n");
            //     printf("2. Se déplacer vers le coup précédent\n");
            //     printf("3. Se déplacer vers l'avant\n");
            //     printf("4. Afficher l'historique des coups joués\n");
            //     printf("5. Quitter\n");
            //     printf("Choix : ");
            //     scanf("%d", &choix);
            //     printf("\n");

                // switch (choix)
                // {
                // case 1:
                //     if (actuel != NULL)
                //     {
                //         if (actuel->suiv != NULL)
                //         {
                //             supprimCoupApres(actuel);
                //         }
                //         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //         scanf("%d", &var1);
                //         printf("\nQuel est la position du joueur ?:");
                //         scanf("%s", var2);
                //         moves = creatMaillon(var1, var2);
                //         L = insTT(L, moves);
                //         actuel = moves;
                //     }
                //     else if (actuel == NULL)
                //     {
                //         if (L == NULL)
                //         {
                //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //             scanf("%d", &var1);
                //             printf("\nQuel est la position du joueur ?:");
                //             scanf("%s", var2);
                //             moves = creatMaillon(var1, var2);
                //             L = insTT(L, moves);
                //             actuel = moves;
                //         }
                //         else if (L != NULL)
                //         {
                //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //             scanf("%d", &var1);
                //             printf("\nQuel est la position du joueur ?:");
                //             scanf("%s", var2);
                //             moves = creatMaillon(var1, var2);
                //             actuel = moves;
                //             moves->suiv = L;
                //             L = moves;
                //             moves->suiv->prec = moves;
                //             supprimCoupApres(actuel);
                //         }
                //     }
                //     break;
                // case 2:
                //     actuel = deplacArriere(actuel);
                //     if (actuel != NULL)
                //         printf("Voici le coup précédent : %s", actuel->position);
                //     else
                //     {
                //         printf("Liste vide!\n");
                //     }
                //     break;
                // case 3:
                //     actuel = deplacAvant(actuel, L);
                //     if (actuel != NULL)
                //         printf("Vous êtes revenu au coup : %s\n", actuel->position);
                //     else
                //     {
                //         printf("Vous êtes à votre dernier coup!\n");
                //     }
                //     break;
                // case 4:
                //     printMoveHistory(L, actuel);
                //     break;
                // case 5:
                //     printf("Au revoir !\n");
                //     break;
                // default:
                //     printf("Choix invalide, veuillez entrer une option valide.\n");
                // }
        //     }
        // }

        

        

        

        // Move *chargerHistorique()
        // {
        //     Move *L = NULL;
        //     FILE *fichier;
        //     char ligne[10];
        //     int joueur;
        //     char position[3];
        //     fichier = fopen("historique.bi", "rb");
        //     if (fichier != NULL)
        //     {
        //         while (fgets(ligne, 10, fichier) != NULL)
        //         {
        //             sscanf(ligne, "%d;%s", &joueur, position);
        //             Move *moves = creatMaillon(joueur, position);
        //             L = insTT(L, moves);
        //         }
        //     }
        //     fclose(fichier);
        //     return L;
        // }

        // int main()
        // {
        //     Move *L, *moves, *actuel;
        //     int choix = 0, var1 = 0;
        //     char var2[3];
        //     L = NULL;
        //     actuel = NULL;
        //     while (choix != 5)
        //     {
        //         printf("\nMenu :\n");
        //         printf("1. Ajouter un coup joué\n");
        //         printf("2. Se déplacer vers le coup précédent\n");
        //         printf("3. Se déplacer vers l'avant\n");
        //         printf("4. Afficher l'historique des coups joués\n");
        //         printf("5. Quitter\n");
        //         printf("Choix : ");
        //         scanf("%d", &choix);
        //         printf("\n");

        //         switch (choix)
        //         {
                // case 1:
                //     if (actuel != NULL)
                //     {
                //         if (actuel->suiv != NULL)
                //         {
                //             supprimCoupApres(actuel);
                //         }
                //         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //         scanf("%d", &var1);
                //         printf("\nQuel est la position du joueur ?:");
                //         scanf("%s", var2);
                //         moves = initAction(var1, var2);
                //         L = insTT(L, moves);
                //         actuel = moves;
                //     }
                //     else if (actuel == NULL)
                //     {
                //         if (L == NULL)
                //         {
                //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //             scanf("%d", &var1);
                //             printf("\nQuel est la position du joueur ?:");
                //             scanf("%s", var2);
                //             moves = initAction(var1, var2);
                //             L = insTT(L, moves);
                //             actuel = moves;
                //         }
                //         else if (L != NULL)
                //         {
                //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
                //             scanf("%d", &var1);
                //             printf("\nQuel est la position du joueur ?:");
                //             scanf("%s", var2);
                //             moves = initAction(var1, var2);
                //             actuel = moves;
                //             moves->suiv = L;
                //             L = moves;
                //             moves->suiv->prec = moves;
                //             supprimCoupApres(actuel);
                //         }
                //     }
                //     break;
        //         case 2:
        //             actuel = deplacArriere(actuel);
        //             if (actuel != NULL)
        //                 printf("Voici le coup précédent : %s", actuel->position);
        //             else
        //             {
        //                 printf("Liste vide!\n");
        //             }
        //             break;
        //         case 3:
        //             actuel = deplacAvant(actuel, L);
        //             if (actuel != NULL)
        //                 printf("Vous êtes revenu au coup : %s\n", actuel->position);
        //             else
        //             {
        //                 printf("Vous êtes à votre dernier coup!\n");
        //             }
        //             break;
        //         case 4:
        //             printMoveHistory(L, actuel);
        //             break;
        //         case 5:
        //             printf("Au revoir !\n");
        //             break;
        //         default:
        //             printf("Choix invalide, veuillez entrer une option valide.\n");
        //         }
        //     }
        //     return 0;
        // }

                   // Main de Manon
        //            Move *LG = NULL,
        //                 *L = NULL;
        // char rep[3];
        // respectRegles(rep, LG, L);

        // Main de Latifa
        // - débug de la gestion d'historique de coups ---------------------------------------------
        // Move *L, *moves, *actuel;
        // int choix = 0, var1 = 0;
        // char var2[3];
        // L = NULL;
        // actuel = NULL;

        // char choix_reprendre;
        // printf("Voulez-vous reprendre la partie sauvegardée ? (O/N) : ");
        // scanf("%c", &choix_reprendre);
        // if (choix_reprendre == 'O' || choix_reprendre == 'o')
        // {
        //     L = chargerHistorique();
        //     actuel = L;
        //     while (actuel->suiv != NULL)
        //     {
        //         actuel = actuel->suiv;
        //     }
        //     printf("Vous avez repris la partie depuis l'historique sauvegardé.\n");
        // }
        // else
        // {
        //     printf("Nouvelle partie démarrée.\n");
        // }

        // while (choix != 6)
        // {
        //     printf("\nMenu :\n");
        //     printf("1. Ajouter un coup joué\n");
        //     printf("2. Se déplacer vers le coup précédent\n");
        //     printf("3. Se déplacer vers l'avant\n");
        //     printf("4. Afficher l'historique des coups joués\n");
        //     printf("5. Sauvegarder la partie en cours\n");
        //     printf("6. Quitter\n");
        //     printf("Choix : ");
        //     scanf("%d", &choix);
        //     printf("\n");

        //     switch (choix)
        //     {
            // case 1:
            //     if (actuel != NULL)
            //     {
            //         if (actuel->suiv != NULL)
            //         {
            //             supprimCoupApres(actuel);
            //         }
            //         printf("\nJoueur (1 pour noir ou 2 pour blanc):");
            //         scanf("%d", &var1);
            //         printf("\nQuel est la position du joueur ?:");
            //         scanf("%s", var2);
            //         moves = creatMaillon(var1, var2);
            //         L = insTT(L, moves);
            //         actuel = moves;
            //     }
            //     else if (actuel == NULL)
            //     {
            //         if (L == NULL)
            //         {
            //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
            //             scanf("%d", &var1);
            //             printf("\nQuel est la position du joueur ?:");
            //             scanf("%s", var2);
            //             moves = creatMaillon(var1, var2);
            //             L = insTT(L, moves);
            //             actuel = moves;
            //         }
            //         else if (L != NULL)
            //         {
            //             printf("\nJoueur (1 pour noir ou 2 pour blanc):");
            //             scanf("%d", &var1);
            //             printf("\nQuel est la position du joueur ?:");
            //             scanf("%s", var2);
            //             moves = creatMaillon(var1, var2);
            //             actuel = moves;
            //             moves->suiv = L;
            //             L = moves;
            //             moves->suiv->prec = moves;
            //             supprimCoupApres(actuel);
            //         }
            //     }
            //     break;
        //     case 2:
        //         actuel = deplacArriere(actuel);
        //         if (actuel != NULL)
        //             printf("Voici le coup précédent : %s", actuel->position);
        //         else
        //         {
        //             printf("Liste vide!\n");
        //         }
        //         break;
        //     case 3:
        //         actuel = deplacAvant(actuel, L);
        //         if (actuel != NULL)
        //             printf("Vous êtes revenu au coup : %s\n", actuel->position);
        //         else
        //         {
        //             printf("Vous êtes à votre dernier coup!\n");
        //         }
        //         break;
        //     case 4:
        //         printMoveHistory(L, actuel);
        //         break;
        //     case 5:
        //         sauvegarderHistorique(L, actuel);
        //         break;
        //     case 6:
        //         printf("Au revoir !\n");
        //         break;
        //     default:
        //         printf("Choix invalide, veuillez entrer une option valide.\n");
        //     }
        // }
        // return 0;