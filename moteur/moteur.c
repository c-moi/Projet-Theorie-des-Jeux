#include "moteur.h"


int moteurJeu(void* DATA)
{

    Move* maillon = NULL;
    // init historique coups
    Move *histoCp = NULL;

    // position dans l'historique
    Move *actuelG = NULL;
    Move* actuelH = NULL;

    // choix action joueur
    int action = 0;

    // initialisation des joueurs
    char* rep = NULL; 







    // On s'assure que l'affichage de bienvenu s'est affiché
    SDL_Delay(1000);

    // initialisation du jeu
    initPlto();
    actuelG = deplacFin(listeG);


    //Chargement de partie si souhaité                                              //
    char choix_reprendre;                                                           //
    printf("\nVoulez-vous reprendre la partie sauvegardée ? (O/N) : ");             //
    scanf("%c", &choix_reprendre);                                                  //
    if (choix_reprendre == 'O' || choix_reprendre == 'o')                           //
    {                                                                               //
        histoCp = chargerHistorique(histoCp);                                       //
        actuelG->suiv = histoCp;                                                    // Latifa, j'ai pas fait de modif
                                                                                    // pour l'implémenter, donc pense
        while (actuelG->suiv != NULL)                                               // à le tester (et si tu veux bien,
        {                                                                           // l'optimiser un peu)
            actuelG = actuelG->suiv;                                                  //
        }                                                                           //
        printf("Vous avez repris la partie depuis l'historique sauvegardé.\n");     //
    }                                                                               //
    else                                                                            //
    {                                                                               //
        printf("Nouvelle partie démarrée.\n");                                      //
    }                                                                               //


    parametres jeu;                                               
    jeu = configPlayers(jeu);

    // boucle de jeu
    while (action != 6)
    {
        // configuration action du joueur
        action = 0;

        rep = malloc(sizeof(char) * 3);

        SDL_Delay(1000);

        // demande à l'utilisateur ce qu'il veut faire
        printf("\n Menu :\n");
        printf("1. Jouer un coup \n");
        printf("2. Se déplacer vers le coup précédent \n");
        printf("3. Se déplacer vers l'avant \n");
        printf("4. Afficher l'historique des coups joués \n");
        printf("5. Sauvegarder la partie en cours\n");
        printf("6. Quitter \n");
        printf("\nQuel est votre choix : ");
        scanf("%d", &action);
        printf("\n");

        switch (action)
        {
            case 1:
                // il faut faire cette demande dans joueur.
                while (strlen(rep) != 2)
                {
                    printf("Quel est la position du joueur : ");
                    fgets(rep, 3*sizeof(char), stdin);
                }
                maillon = creatMaillon(jeu.tourJoueur, rep);
                printf("Le joueur %d joue en %s \n", jeu.tourJoueur, maillon->position);
                respectRegles(&histoCp, &actuelG, &actuelH, maillon, &jeu);
                break;
            case 2:
                deplacArriere(&actuelG, &actuelH, histoCp);
                break;
            case 3:
                deplacAvant(&actuelG, &actuelH, histoCp);
                break;
            case 4:
                printMoveHistory(histoCp, actuelH);
                break;
            case 5:
                // sauvegarderHistorique(histoCp, actuelG); Latifa, il faut que tu adaptes pour qu'on 
                break;                                  // soit entre de début de histo et fin avecactuelG
            case 6:                                     // Attention à bien faire tes tests !
                printf("Au revoir ! \n");
                break;

            default:
                printf("Choix invalide, ceci n'est pas une action possible... \n");
                break;
        }
        free(rep);
    }
    exit(0);
}

void initPlto()
{
    SDL_LockMutex(mutexG);
    listeG = insTT(listeG, creatMaillon(1, "d4"));
    listeG = insTT(listeG, creatMaillon(2, "d5"));
    listeG = insTT(listeG, creatMaillon(1, "e5"));
    listeG = insTT(listeG, creatMaillon(2, "e4"));
    SDL_UnlockMutex(mutexG);

}

Move *creatMaillon(int joueur, char position[3])
{
    Move *maillon;
    maillon = (Move*) malloc(sizeof(Move));
    if(maillon == NULL)
    {
        printf("\nAllocation impossible");
    }
    else 
    {
        maillon->joueur=joueur;
        strcpy(maillon->position, position);
        maillon->prec=NULL;
        maillon->suiv=NULL;
    }
    return maillon;
}


Move *insTT(Move *Liste, Move *moves)
{
    Move *dep = Liste;
    if (Liste == NULL)
    {
        Liste = moves;
        Liste->prec = NULL;
        Liste->suiv = NULL;
    }
    else
    {
        dep = deplacFin(dep);
        moves->suiv = dep->suiv;
        moves->prec = dep;
        dep->suiv = moves;
    }
    return Liste;
}

Move *deplacFin(Move *Liste)
{
    Move* tmp = Liste;
    if (tmp != NULL)
    {
        while (tmp->suiv != NULL)
        {
            tmp = tmp->suiv;
        }
    }
    return tmp;
}



void respectRegles(Move** historique, Move** actuelG, Move** actuelH, Move* Maillon, parametres *jeu)
{
    int pre = 0;
    Move* tst = listeG;
    if ((Maillon->position[0] >= 97 && Maillon->position[0] <= 104) && (Maillon->position[1] >= 49 && Maillon->position[1] <= 56))
    {
        while (tst != NULL)
        {
            if (strcmp(tst->position, Maillon->position) == 0)
            {
                pre = 1;
            }
            tst = tst->suiv;
        }

        if (pre == 1)
        {
            printf("Position impossible car la case est déjà occupée\n");
        }
        else
        {

            printf("La case est vide\n");
            Maillon->switched = verifAllie(Maillon->position, jeu);

            
            // en attendant :
            if (Maillon->switched != NULL)
            {
                if (*historique == NULL)
                {
                    *historique = insTT(*historique, creatMaillon(Maillon->joueur, Maillon->position));
                    *actuelH = *historique;
                }
                else 
                {
                    if (*actuelH == NULL)
                    {
                        *historique = supprimCoupApres(*historique);
                        free(*historique);
                        *historique = insTT(*historique, creatMaillon(Maillon->joueur, Maillon->position));
                        *actuelH = *historique;
                    }
                    if (*actuelH != NULL)                   //                                       //
                    {   
                        if ((*actuelH)->suiv != NULL)   
                        {                                          //                                       //
                            *actuelH = supprimCoupApres(*actuelH);  
                        }    
                        Move* maillonH = creatMaillon(Maillon->joueur, Maillon->position);
                        *historique = insTT(*historique, maillonH);
                        *actuelH = maillonH;                 //                                       //
                    }
                }
                retournPions(Maillon->switched);
                                                              //                                       //  
                                                            // à déplacer en fonction                //          
                SDL_LockMutex(mutexG);                         // de ce que tu veux faire               //
                listeG = insTT(listeG, Maillon);               // (au niveau de l'appel de fonction)    //
                SDL_UnlockMutex(mutexG);                       // référence à ligne 92                  //
                *actuelG = Maillon;

                jeu->tourJoueur = (jeu->tourJoueur % 2)+ 1;   
            }
            else
            {
                printf("Cela ne permet de retourner aucun pion, le coup n'a pas été retenu !\n");
            }

         
        }
    }
    else
    {
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }
}



void deplacArriere(Move** actuelG, Move** actuelH, Move* histoCp)
{
    if (histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    if (histoCp != NULL)
    {
        if (estDans((*actuelG)->position, histoCp) == NULL)
        {
            printf("Vous êtes au début du jeu !\n");
        }
        else if (estDans((*actuelG)->position, histoCp) != NULL)
        {
            Move *tmp = *actuelG;
            *actuelG = (*actuelG)->prec;
            (*actuelG)->suiv = NULL;
            free(tmp);

            if (*actuelH != NULL)
                *actuelH = (*actuelH)->prec;

            printf("%s\n", (*actuelG)->position);
            if (estDans((*actuelG)->position, histoCp) == NULL)
            {
                printf("Vous êtes revenu au début du jeu !\n");
            }
            else if (estDans((*actuelG)->position, histoCp) != NULL)
            {
                printf("Vous êtes revenu au coup : %s\n", (*actuelG)->position);
            }
        }
    }
}

void deplacAvant(Move** actuelG, Move** actuelH, Move* histoCp)
{
    if (histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (histoCp != NULL)
    {
        if (*actuelH != NULL)
        {
            if ((*actuelH)->suiv != NULL)
            {
                *actuelH = (*actuelH)->suiv;
                *actuelG = insTT(*actuelG, creatMaillon((*actuelH)->joueur, (*actuelH)->position));
                *actuelG = (*actuelG)->suiv;
                printf("Vous êtes revenu au coup : %s\n", (*actuelH)->position);
            }
            else
            {
                printf("Vous êtes à votre dernier coup joué !\n");
            }
        }
        else
        {
            *actuelH = histoCp;
            *actuelG = insTT(*actuelG, creatMaillon(histoCp->joueur, histoCp->position));
            *actuelG = (*actuelG)->suiv;
            printf("Vous êtes revenu au coup : %s\n", (*actuelH)->position);
        }
    }
}

Move* estDans(char pion[3], Move *L)
{
    Move *ptr1 = L;                        
                                             
    while(ptr1 != NULL)
    {
        if(strcmp(pion, ptr1->position) == 0)
        {
            return ptr1;
        }
        else
        {
            ptr1 = ptr1->suiv;
        }
    }
    return NULL;
}

void printMoveHistory(Move *Liste, Move *End)
{
    int cpt = 0;
    if (Liste == NULL)
    {
        printf("\n Historique de jeu vide ! \n");
    }
    else if (Liste != NULL)
    {
        if (estDans(End->position, Liste) == NULL)
        {
            printf("\n Historique de jeu vide ! \n");
        }
        else if(estDans(End->position, Liste) != NULL)
        {
            while (Liste != End)
            {
                printf("Mouvement %d : %d a joué en (%s)\n", cpt + 1, Liste->joueur, Liste->position);
                Liste = Liste->suiv;
                cpt++;
            }
            printf("Mouvement %d : %d a joué en (%s)\n", cpt + 1, Liste->joueur, Liste->position);
        }
    }
}

Move* supprimCoupApres(Move *liste)
{
    Move* actuel = liste;
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
    return actuel;
}






// Manon, A compléter, je ne la touche pas 



Move* verifAllie(char rep[3], parametres* jeu)
{
    Move *L = verifContour(rep, jeu);
    Move* a_tourner = NULL;
    char *rech = malloc(3*sizeof(char));

    char *recl = malloc(3*sizeof(char));
    if(L != NULL)
    {
        while (L != NULL)
        {
            rech = L->position;
            recl = rech;
            // Si pion adverse en haut à gauche
            if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1] - 1))
            {
                a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                for (int i=1; i<=(rech[0]-96) || i<=(rech[1]-49); i++)
                {
                    recl[0] -= i;
                    recl[1] -= i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            a_tourner = supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
                
            }
            // Si pion adverse au dessus
            else if (rech[0] == (rep[0]) && rech[1] == (rep[1] - 1))
            {
                for (int i=0; i<(rech[1]-49); i++)
                {
                    recl[1] -= i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en haut à droite
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1] - 1))
            {
                for (int i=0; i<(104-rech[0]) || i<(rech[1]-49); i++)
                {
                    recl[0] += i;
                    recl[1] -= i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse à gauche
            else if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1]))
            {
                for (int i=0; i<(rech[0]-96); i++)
                {
                    recl[0] -= i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse à droite
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1]))
            {
                for (int i=0; i<(104-rech[0]); i++)
                {
                    recl[0] += i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            //printf("a droite\n");  ici ?
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en bas à gauche
            else if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1] + 1))
            {
                
                for (int i=0; i<(rech[0]-96) || i<(56-rech[1]); i++)
                {
                    recl[0] -= i;
                    recl[1] += i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en dessous
            else if (rech[0] == (rep[0]) && rech[1] == (rep[1] + 1))
            {
                for (int i=0; i<(56-rech[1]); i++)
                {
                    recl[1] += i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en bas à droite
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1] + 1))
            {
                for (int i=0; i<(104-rech[0]) || i<(56-rech[1]); i++)
                {
                    recl[0] += i;
                    recl[1] += i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            a_tourner = insTT(a_tourner, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (a_tourner != NULL)
                        {
                            supprimCoupApres(a_tourner);
                            free(a_tourner);
                            a_tourner = NULL;
                        }
                        break;
                    }
                }
            }
            

            L = L->suiv;
        }
        return a_tourner;
    }
    else
    {
        return NULL;
    }
}

Move* verifContour(char rep[3], parametres* jeu)
{
    Move *listadv = NULL;
    Move* tmp;
    char rec[3];

    for ((rec[0]) = ((rep[0]) - 1); (rec[0]) <= ((rep[0]) + 1); (rec[0])++)
    {
        for ((rec[1]) = ((rep[1]) - 1); (rec[1]) <= ((rep[1]) + 1); (rec[1])++)
        {
            tmp = listeG;
            while (tmp != NULL)
            {
                if (strcmp(rec, tmp->position) == 0 && tmp->joueur == (jeu->tourJoueur % 2)+ 1)
                {
                    listadv = insTT(listadv, creatMaillon((jeu->tourJoueur % 2)+ 1, rec));
                }
                tmp = tmp->suiv;
            }
        }
    }

    if (listadv == NULL)
    {
        printf("Emplacement impossible car aucun pion adverse autour\n");
    }
    return listadv;
}

void retournPions(Move *a_retourner){
    Move *ptr = listeG;
    while(ptr != NULL){
        if(strcmp(a_retourner->position, ptr->position) == 0){
            ptr->joueur = (ptr->joueur %2) + 1;
        }
        ptr = ptr->suiv;
    }
    AfficheListe(ptr);
}

void AfficheListe(const Move * l)
{
    for ( ; l != NULL; l = l->suiv)
    {
        printf("%s " "%d", l->position, l->joueur);
    }
    printf("\n");
}