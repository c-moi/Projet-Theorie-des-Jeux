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

    Move* maillon=NULL;
    // init historique coups
    Move *histoCp=NULL;
    // init pions noirs
    Move *List_J1=NULL;
    // init pions blancs
    Move *List_J2=NULL;

    // position dans l'historique
    Move *actuelG=NULL;
    Move* actuelH=NULL;

    // choix action joueur
    int action;

    // initialisation des joueurs
    char* rep; 

    int tour=60;

    parametres jeu;





    // On s'assure que l'affichage de bienvenu s'est affiché
    SDL_Delay(1000);
                                            //

    // boucle de jeu
    while (action != 6)
    {
        if(tour<60){
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
                    printf("Le joueur %d joue en %s \n", maillon->joueur, maillon->position);
                    // Manon, soit tu as une fonction de cette longueur si tu fait les changements dans respectRegles
                    // soit tu fais les changements ici mais dans ce cas, il te faut retourner un booléen pour
                    // dire si oui ou non le coup est valide. A toi de voir.
                    respectRegles(&histoCp, &actuelG, &actuelH, maillon, List_J1, List_J2, &jeu, &tour);
                    break;
                case 2:
                    deplacArriere(&actuelG, &actuelH, &histoCp, jeu);
                    break;
                case 3:
                    deplacAvant(&actuelG, &actuelH, histoCp, jeu);
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
        }
        else 
        {
            printf("bdfbhdv\n");
            char restart;
            printf("La partie est fini. Voulez vous recommencer une partie ? (O/N)");
            scanf("%c", &restart);
            if (restart=='O' || restart=='o')
            {
                tour=0;
                printf("hdhfbhdf\n");
                if(maillon!=NULL)
                {
                    free(maillon);
                }  
                maillon = NULL;
                
                if(listeG!=NULL)
                {
                    supprimCoupApres(listeG);
                    free(listeG);
                }
                listeG=NULL;
                
                // init historique coups
                if(histoCp!=NULL)
                {
                    
                    supprimCoupApres(histoCp);
                    free(histoCp);
                    
                }  
                
                histoCp = NULL;
                // init pions noirs
                //List_J1 = NULL;
                // init pions blancs
                //List_J2 = NULL;
                

                // position dans l'historique
                actuelG = NULL;
                actuelH = NULL;

                // choix action joueur
                action = 0;

                // initialisation des joueurs
                rep = NULL; 

                char choix_reprendre;





                // On s'assure que l'affichage de bienvenu s'est affiché
                SDL_Delay(1000);

                // initialisation du jeu
                initPlto(&List_J1, &List_J2);
                actuelG = deplacFin(listeG);


                // rep[3] = configPlayers(listeG, rep); // à modifier                           // Manon, Il faut changer ça
                // En attendant :                                                               //
                jeu.nbJoueurs=1;
                jeu.lvlOrdi=0;
                jeu.tourJoueur=1;                                                     //

                //Chargement de partie si souhaité                                              //      
                if (access("fichier/historique.bin", F_OK) ==0)
                {                                                                     //
                    printf("\nVoulez-vous reprendre la partie sauvegardée ? (O/N) : "); 
                    viderBuffer();            //
                    scanf("%c", &choix_reprendre);                                                  //
                    if (choix_reprendre == 'O' || choix_reprendre == 'o')                           //
                    {                    
                        printf("tour2: %d\n", tour);                                                        //
                        chargerHistorique(&listeG, &actuelG, &histoCp, &actuelH, &tour);  

                        printf("Vous avez repris la partie depuis l'historique sauvegardé.\n");     //
                    }                                                                               //
                    else                                                                            //
                    {                                                                               //
                        printf("Nouvelle partie démarrée.\n");                                     //
                    } 
                    remove("fichier/historique.bin");
                }    
                else 
                {
                    printf("Le fichier n'existe pas!\n");
                }       
            }
            else
            {
                action=6;
                
            }
        }
        
    }
    exit(0);
}

void initPlto(Move** LN, Move** LB)
{
    SDL_LockMutex(mutexG);
    listeG = insTT(listeG, creatMaillon(1, "d4"));
    listeG = insTT(listeG, creatMaillon(2, "d5"));
    listeG = insTT(listeG, creatMaillon(1, "e5"));
    listeG = insTT(listeG, creatMaillon(2, "e4"));
    SDL_UnlockMutex(mutexG);

    // Manon, insére listesN et B
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


void respectRegles(Move** historique, Move** actuelG, Move** actuelH, Move* Maillon, Move* List_J1, Move* List_J2, parametres *jeu, int* tour)
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
            // ###### A ADAPTER ######

             printf("La case est vide\n");

            // ( MANON )
            // pour le moment, on va se contenter de ces tests la pour les autres parties
            // ("cela correspond à une case du tableau" et "la case est vide")
            // Il faudra regler les problèmes de verifContours car le seg fault qui est
            // produit est dû au fait que list_j1 et list_j2 sont nulles
            
            // en attendant :
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
            }                                              //                                       //  
                                                           // à déplacer en fonction                //          
            SDL_LockMutex(mutexG);                         // de ce que tu veux faire               //
            listeG = insTT(listeG, Maillon);               // (au niveau de l'appel de fonction)    //
            SDL_UnlockMutex(mutexG);                       // référence à ligne 92                  //
            *actuelG = Maillon;
                                                           //                                       //
                                                           //                                       //
                                                           //                                       //         
                                                           //                                       // il faudra que tu testes
            jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;   //                                       // tout ça après ton verifContour
                                                                                                    //
                                                                                                    //
            // if(jeu->tourJoueur==1)                      //                                       //
            // {                                           //                                       //
            //     insTT(List_J1, move);                   //                                       //
            // }                                           // J'imagine que ça va la ca             //
            // else                                        //                                       //
            // {                                           //                                       //
            //     insTT(List_J2, move);                   //                                       //
            // }                                           //                                       //     

            // fonction qui fait le tour de rep
            //verifContour(Maillon->position, Liste, List_J1, List_J2, pre);
            // L->suiv=rep; à mettre à la fin si tt les conditions sont vérifiées
            (*tour)++;
            printf("tour:%d\n", *tour);
        }
    }
    else
    {
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }
}

// Manon, il faut adapter et tester ça, je n'y ai pas touché
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
            }
            j++;
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


// Manon, A compléter et tester, je ne la touche pas

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

void deplacArriere(Move** actuelG, Move** actuelH, Move** histoCp, parametres jeu)
{
    if (*histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (*histoCp != NULL)
    {
        for(int i=0 ; i<((jeu.nbJoueurs%2)+1); i++){
            if (estDans((*actuelG)->position, *histoCp) == 0)
            {
                printf("Vous êtes au début du jeu !\n");
            }
            else if (estDans((*actuelG)->position, *histoCp) == 1)
            {
                Move *tmp = *actuelG;
                *actuelG = (*actuelG)->prec;
                (*actuelG)->suiv = NULL;
                free(tmp);

                if (*actuelH != NULL)
                    *actuelH = (*actuelH)->prec;

                printf("%s\n", (*actuelG)->position);
                if (estDans((*actuelG)->position, *histoCp) == 0)
                {
                    printf("Vous êtes revenu au début du jeu !\n");
                }
                else if (estDans((*actuelG)->position, *histoCp) == 1)
                {
                    printf("Vous êtes revenu au coup : %s\n", (*actuelG)->position);
                }
            }
        }
    
    }
}

void deplacAvant(Move** actuelG, Move** actuelH, Move* histoCp, parametres jeu)
{
    if (histoCp == NULL)
    {
        printf("Vous ne pouvez pas revenir à un coup joué, aucune action n'a été faite au préalable !\n");
    }
    else if (histoCp != NULL)
    {
        for(int i=0 ; i<((jeu.nbJoueurs%2)+1);i++){
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
}

int estDans(char pion[3], Move *L)
{
    //char *ptr1 = L;                        // Manon Pas besoin de ça puisque L est une copie du pointeur de la liste
                                             // aucun des changements de ce pointeur de sera retenu puisque pas de return
                                             // J'ai changé parce que ça causait une boucle infinie
    int j = 0;

    while(L != NULL)
    {
        if(strcmp(pion, L->position) == 0)
        {
            j = 1;
            break;
        }
        else
        {
            L = L->suiv;
        }
    }
    return j;
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
        if (estDans(End->position, Liste) == 0)
        {
            printf("\n Historique de jeu vide ! \n");
        }
        else if(estDans(End->position, Liste) == 1)
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


//Supprimer un élément d'une liste
Move* supprimerElement(Move* list, char valeur[3])
{
    Move  *tmp;
    Move  *previous;
    
    if (list == NULL) // si la liste est NULL on s'arrete tout de suite
    return (list);
    previous = list;
    if (previous->position == valeur) // Verifie la tete de liste, cas particulier
    {
    list = previous->suiv;
    free(previous);
    return (list);
    }
    tmp = previous->suiv; // le cas n est gere on se place donc sur le cas n+1
    while(tmp != NULL) // On Mouline est on supprime si on trouve l'element
    {
    if (tmp->position == valeur)
    {
        previous->suiv = tmp->suiv;
        free(tmp);
        return (list);
    }
    previous = tmp; // pour ce souvenir dans la prochaine iteration du precedent
    tmp = tmp->suiv;
    }
    return list;
}



// Manon, A compléter, je ne la touche pas 

void retournPions(char pionallie[3], char rep[3], char tour[3], Move *LG, Move *L1, Move *L2){
    tour=rep;
    //retourne les pions de la colonne au-dessus
    if("colonne dessus"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[1]=tour[1]-1;
        }
    }
    //retourne les pions de la colonne en-dessous
    if("colonne dessous"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[1]=tour[1]+1;
        }
    }
    //retourne les pions de la ligne à gauche
    if("ligne gauche"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]-1;
        }
    }
    //retourne les pions de la ligne à droite
    if("ligne droite"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]+1;
        }
    }
    //retourne les pions de la diagonale au-dessus à gauche
    if("diag haut gauche"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]-1;
            tour[1]=tour[1]-1;
        }
    }
    //retourne les pions de la diagonale au-dessus à droite
    if("diag haut droite"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]+1;
            tour[1]=tour[1]-1;
        }
    }
    //retourne les pions de la diagonale en-dessous à gauche
    if("diag bas gauche"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]-1;
            tour[1]=tour[1]+1;
        }
    }
    //retourne les pions de la diagonale en-dessous à droite
    if("diag bas droite"){
        while(strcmp(tour,pionallie)!=0){
            if(LG->joueur==1){
                supprimerElement(L2, tour);
                insTT(L1, creatMaillon(1,tour));
            }
            else{
                supprimerElement(L1, tour);
                insTT(L2, creatMaillon(1,tour));
            }
            tour[0]=tour[0]+1;
            tour[1]=tour[1]+1;
        }
    }
}