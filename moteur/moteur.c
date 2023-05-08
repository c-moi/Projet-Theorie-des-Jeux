#include "moteur.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int moteurJeu(void* DATA)
{
    Move* maillon = NULL;
    // init historique coups
    Move *histoCp = NULL;

    // position dans l'historique
    Move *actuelG = NULL;
    Move* actuelH = NULL;

    // choix action joueur
    int action;

    // initialisation des joueurs
    char* rep; 

    int tour = 60;

    parametres jeu;





    // On s'assure que l'affichage de bienvenu s'est affiché
    SDL_Delay(1000);

    // boucle de jeu
    while (action != 6)
    {
        if(tour < 60)
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
            viderBuffer();
            scanf("%d", &action);
            printf("\n");

            switch (action)
            {      
                case 1:
                    maillon = tourJoueur(&jeu);
                    printf("Le joueur %d joue en %s \n", jeu.tourJoueur, maillon->position);
                    respectRegles(&histoCp, &actuelG, &actuelH, maillon, &jeu, &tour);
                    break;
                case 2:
                    deplacArriere(&actuelG, &actuelH, histoCp, &jeu);
                    break;
                case 3:
                    deplacAvant(&actuelG, &actuelH, histoCp, &jeu);
                    break;
                case 4:
                    printMoveHistory(histoCp, actuelH);
                    break;
                case 5:
                    sauvegarderHistorique(histoCp, actuelH);
                    break;
                case 6:
                    printf("Au revoir ! \n");
                    break;

                default:
                    printf("Choix invalide, ceci n'est pas une action possible... \n");
                    break;
            }
            free(rep);
            viderBuffer();

            if(tour == 60){
                char restart;
                printf("La partie est fini. Voulez vous recommencer une partie ? (O/N)");
                viderBuffer();
                scanf("%c", &restart);
                
                if (restart == 'O' || restart == 'o')
                {
                    tour = 0;
                    
                    // reinit liste générale
                    if(listeG != NULL)
                    {
                        supprimCoupApres(listeG);
                        free(listeG);
                    }
                    listeG = NULL;
                    
                    // reinit historique coups
                    if(histoCp!=NULL)
                    {
                        histoCp = supprimCoupApres(histoCp);
                        histoCp->switched = supprimCoupApres(histoCp->switched);
                        free(histoCp);
                    }
                    histoCp = NULL;
                    
                    if(maillon != NULL)
                    {
                        maillon->switched = supprimCoupApres(maillon->switched);
                        free(maillon);
                    }  
                    maillon = NULL;
                        
                    // position dans l'historique
                    actuelG = NULL;
                    actuelH = NULL;
                }
                else
                {
                    action=6;
                    
                }
            }
        }
        else 
        {

             // choix action joueur
            action = 0;

            // initialisation des joueurs
            rep = NULL; 

            char choix_reprendre;

            // On s'assure que l'affichage de bienvenu s'est affiché
            SDL_Delay(1000);

            // initialisation du jeu
            initPlto();
            actuelG = deplacFin(listeG);

            jeu = configPlayers(jeu);                        
                                                                    

            //Chargement de partie si souhaité                                              //      
            if (access("fichier/historique.bin", F_OK) == 0)
            {                                                                     //
                printf("\nVoulez-vous reprendre la partie sauvegardée ? (O/N) : "); 
                viderBuffer();            //
                scanf("%c", &choix_reprendre);                                                  //
                if (choix_reprendre == 'O' || choix_reprendre == 'o')                           //
                {                                                      //
                    chargerHistorique(&listeG, &actuelG, &histoCp, &actuelH, &tour);  

                    printf("Vous avez repris la partie depuis l'historique sauvegardé.\n");     //
                }                                                                               //
                else                                                                            //
                {                                                                               //
                    printf("Nouvelle partie démarrée.\n");                                     //
                } 
                remove("fichier/historique.bin");
            }
            tour = 0;
        }
    }
    exit(0);
}

void initPlto()
{
    SDL_LockMutex(mutexG);
    listeG = insTT(listeG, creatMaillon(1, "d4"));
    listeG = insTT(listeG, creatMaillon(1, "e5"));
    listeG = insTT(listeG, creatMaillon(2, "d5"));
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
        maillon->joueur = joueur;
        strcpy(maillon->position, position);
        maillon->prec = NULL;
        maillon->suiv = NULL;
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


void respectRegles(Move** historique, Move** actuelG, Move** actuelH, Move* Maillon, parametres *jeu, int* tour)
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
            
            if (Maillon->switched != NULL)
            {
                if (*historique == NULL)
                {
                    *historique = insTT(*historique, Maillon);
                    *actuelH = *historique;
                }
                else
                {
                    if (*actuelH == NULL)
                    {
                        *historique = supprimCoupApres(*historique);
                        (*historique)->switched = supprimCoupApres((*historique)->switched);
                        free((*historique)->switched);
                        free(*historique);
                        *historique = insTT(*historique, Maillon);
                        *actuelH = *historique;
                    }
                    else if (*actuelH != NULL)                                                          
                    {   
                        if ((*actuelH)->suiv != NULL)   
                        {                                                                                 
                            *actuelH = supprimCoupApres(*actuelH);
                        }    
                        *historique = insTT(*historique, Maillon);
                        *actuelH = Maillon;                                                        
                    }
                }    
                    
                retournPions(Maillon->switched);

                Move* MaillonG = creatMaillon(Maillon->joueur, Maillon->position);
                SDL_LockMutex(mutexG);                         
                listeG = insTT(listeG, MaillonG);               
                SDL_UnlockMutex(mutexG);                       
                *actuelG = MaillonG;

                jeu->tourJoueur = (jeu->tourJoueur % 2)+ 1; 
                (*tour)++;
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

void deplacArriere(Move** actuelG, Move** actuelH, Move* histoCp, parametres *jeu)
{
    
    if (histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (histoCp != NULL)
    {
        for(int i=0 ; i<((jeu->nbJoueurs%2)+1); i++)
        {
            if (estDans((*actuelG)->position, histoCp) == NULL)
            {
                printf("Vous êtes au début du jeu !\n");
            }
            else if (estDans((*actuelG)->position, histoCp) != NULL)
            {
                Move *tmp = *actuelG;

                tmp->switched = supprimCoupApres(tmp->switched);
                free(tmp->switched);
                jeu->tourJoueur = (jeu->tourJoueur % 2)+ 1;

                *actuelG = (*actuelG)->prec;
                (*actuelG)->suiv = NULL;
                free(tmp);

                if (*actuelH != NULL)
                {
                    retournPions((*actuelH)->switched);
                    *actuelH = (*actuelH)->prec;
                }

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
}
     

void deplacAvant(Move** actuelG, Move** actuelH, Move* histoCp, parametres *jeu)
{
    if (histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (histoCp != NULL)
    {
        for(int i=0 ; i<((jeu->nbJoueurs%2)+1);i++)
        {
            if (*actuelH != NULL)
            {
                if ((*actuelH)->suiv != NULL)
                {
                    *actuelH = (*actuelH)->suiv;
                    *actuelG = insTT(*actuelG, creatMaillon((*actuelH)->joueur, (*actuelH)->position));
                    retournPions((*actuelH)->switched);
                    jeu->tourJoueur = (jeu->tourJoueur % 2)+ 1;
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
                retournPions((*actuelH)->switched);
                jeu->tourJoueur = (jeu->tourJoueur % 2)+ 1;
                *actuelG = (*actuelG)->suiv;
                printf("Vous êtes revenu au coup : %s\n", (*actuelH)->position);
            }
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
            
            if (suivant->switched != NULL)
            {
                Move* tmp_swtch = suivant->switched->suiv;
                while(tmp_swtch != NULL)
                {
                    suivant->switched->suiv = tmp_swtch->suiv;
                    if (suivant->switched->suiv != NULL)
                    {
                        suivant->switched->suiv->prec = suivant->switched;
                    }
                    free(tmp_swtch);
                    tmp_swtch = suivant->switched->suiv;
                }
                free(suivant->switched);
            }
            
            free(suivant);
            suivant = actuel->suiv;
        }
    }
    return actuel;
}

Move* verifAllie(char rep[3], parametres* jeu)
{
    Move *L = verifContour(rep, jeu);
    Move* a_tourner = NULL;
    Move *test = NULL;
    char *rech = malloc(3*sizeof(char));

    char *recl = malloc(3*sizeof(char));
    if(L != NULL)
    {
        while (L != NULL)
        {
            rech = L->position;
            strcpy(recl, rech);
            // Si pion adverse en haut à gauche
            if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1] - 1))
            {
                for (int i=0; i<=(rech[0]-97) || i<=(rech[1]-49); i++)
                {

                    recl[0] = (rech[0] - i);
                    recl[1] = (rech[1] - i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 97 || recl[1] == 49){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
                
            }
            // Si pion adverse au dessus
            else if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1]))
            {
                for (int i=0; i<=(rech[0]-97); i++)
                {

                    recl[0] = (rech[0] - i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 97){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }

                }
            }
            // Si pion adverse en haut à droite
            else if (rech[0] == (rep[0] - 1) && rech[1] == (rep[1] + 1))
            {
                for (int i=0; i<=(rech[0] - 97) || i<=(56 - rech[1]); i++)
                {
                    recl[0] = (rech[0] - i);
                    recl[1] = (rech[1] + i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 97 || recl[1] == 56){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse à gauche
            else if (rech[0] == (rep[0]) && rech[1] == (rep[1] - 1))
            {
                for (int i=0; i<=(rech[1]-49); i++)
                {

                    recl[1] =rech[1] - i;

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[1] == 49){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse à droite
            else if (rech[0] == (rep[0]) && rech[1] == (rep[1] + 1))
            {
                for (int i=0; i<=(56-rech[1]); i++)
                {
                    recl[1] = (rech[1]+i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[1] == 56){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en bas à gauche
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1] - 1))
            {
                
                for (int i=0; i<=(104-rech[0]) || i<=(rech[1] - 49); i++)
                {

                    recl[0] = (rech[0] + i);
                    recl[1] = (rech[1] - i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 104 || recl[1] == 49){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en dessous
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1]))
            {
                for (int i=0; i<=(104-rech[0]); i++)
                {

                    recl[0] = (rech[0] + i);
                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 104){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }
                }
            }
            // Si pion adverse en bas à droite
            else if (rech[0] == (rep[0] + 1) && rech[1] == (rep[1] + 1))
            {
                for (int i=0; i<=(104-rech[0]) || i<=(56-rech[1]); i++)
                {

                    recl[0] = (rech[0] + i);
                    recl[1] = (rech[1] + i);

                    if (estDans(recl, listeG) != NULL)
                    {
                        if (estDans(recl, listeG)->joueur == (jeu->tourJoueur % 2)+ 1)
                        {
                            if(recl[0] == 104 || recl[1] == 56){
                                if (test != NULL)
                                {
                                    test = supprimCoupApres(test);
                                    free(test);
                                    test = NULL;
                                }
                                break;
                            }
                            test = insTT(test, creatMaillon((jeu->tourJoueur % 2)+ 1, recl));
                            continue;
                        }
                        else if (estDans(recl, listeG)->joueur == jeu->tourJoueur)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (test != NULL)
                        {
                            test = supprimCoupApres(test);
                            free(test);
                            test = NULL;
                        }
                        break;
                    }

                }
            }
            while(test != NULL){
                
                a_tourner = insTT(a_tourner, creatMaillon(test->joueur, test->position));
                test = test->suiv;
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

void retournPions(Move *a_retourner)
{
    Move *ptr = listeG;
    Move *ptr2 = a_retourner;
    while(ptr != NULL)
    {
        ptr2 = a_retourner;
        while(ptr2 != NULL)
        {
            if(strcmp(ptr2->position, ptr->position) == 0)
            {
                ptr->joueur = (ptr->joueur %2) + 1;
            }
            ptr2 = ptr2->suiv;
        }
        ptr = ptr->suiv;
    }
}    

void AfficheListe(const Move * l)
{
    for (l; l != NULL; l = l->suiv)
    {
        printf("%d \n" " %s\n", l->joueur, l->position);
    }
    printf("\n");
}
