#include "moteur.h"



int moteurJeu(void *listeG)
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

   // rep[3] = configPlayers(listeG, rep); // à modifier

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
                    respectRegles(actuel, maillon, List_J1, List_J2, &jeu); // à mettre dans respectRegles
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
                        respectRegles(actuel, maillon, List_J1, List_J2, &jeu); // à mettre dans respectRegles
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
                        respectRegles(actuel, maillon, List_J1, List_J2, &jeu); // à mettre dans respectRegles
                        actuel = maillon; // à mettre dans respectRegles
                        maillon->suiv = histoCp; // à mettre dans respectRegles
                        histoCp = maillon; // à mettre dans respectRegles                // a inserer a la fin de respect regles si tt les conditions sont valides
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
    return 0;
}

Move *initPlto(Move *liste, Move *LN, Move *LB)
{
    liste = insTT(liste, creatMaillon(1, "d4"));
    liste = insTT(liste, creatMaillon(2, "e4"));
    liste = insTT(liste, creatMaillon(1, "d5"));
    liste = insTT(liste, creatMaillon(2, "e5"));
    LN = insTT(LN, creatMaillon(1, "d4"));
    LN = insTT(LN, creatMaillon(1, "d5"));
    LB = insTT(LB, creatMaillon(2, "e4"));
    LB = insTT(LB, creatMaillon(2, "e5"));

    return liste;
}

Move *listAdverse(Move *liste, Move *List_J1, Move *List_J2){
    Move *L;
    if(liste->joueur == 1){
        L = List_J2;
    }
    else{
        L = List_J1;
    }
    return L;
}

Move *creatMaillon(int joueur, char position[3]){
    Move *maillon;
    maillon=(Move*)malloc(sizeof(Move));
    if(maillon == NULL){
        printf("\nAllocation impossible");
    }
    else {
        maillon->joueur=joueur;
        strcpy(maillon->position, position);
        maillon->prec=NULL;
        maillon->suiv=NULL;
    }
    return maillon;
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


Move* respectRegles(Move* Liste, Move* Maillon, Move* List_J1, Move* List_J2, parametres *jeu)
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
             printf("La case est vide\n");
            // fonction qui fait le tour de rep
             verifContour(Maillon->position, Liste, List_J1, List_J2, pre, jeu);
        }
    }
    else
    {
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }

    return Liste;
}

void verifContour(char rep[3], Move *LG, Move *List_J1, Move *List_J2, int pre, parametres *jeu)
{
    Move *listadv = NULL;
    int i = 1;
    int j = 0;
    char rec[3];
    rec[0] = rep[0] - 1;
    while (j < 3)
    {
        for ((rec[1]) = ((rep[1]) - 1); (rec[1]) = ((rep[1]) + 1); (rec[1])++)
        {
            if (strcmp(rec, listAdverse(LG, List_J1, List_J2)->position) == 0)
            {
                insTT(listadv, creatMaillon(2, rec));
                printf("Emplacement possible\n");
                verifAllie(rec, rep, LG, List_J1, List_J2, pre, jeu);
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
            if (strcmp(rec, listAdverse(LG, List_J1, List_J2)->position) == 0)
            {
                insTT(listadv, creatMaillon(2, rec));
                printf("Emplacement possible\n");
                verifAllie(rec, rep, LG, List_J1, List_J2, pre, jeu);
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
            if (strcmp(rec, listAdverse(LG, List_J1, List_J2)->position))
            {
                insTT(listadv, creatMaillon(2, rec));
                printf("Emplacement possible\n");
                verifAllie(rec, rep, LG, List_J1, List_J2, pre, jeu);
                i = 0;
            }
            else
            {
                i++;
            }
        }
        j++;
    }
    if (i != 0)
    {
        printf("Emplacement impossible car aucun pion adverse autour\n");
    }
}

int estDans(char pion[3], Move *L){
    char *ptr1=L->position;
    int j=1;
    while(ptr1!=NULL){
        if(strcmp(pion, ptr1)==0){
            j=0;
            break;
        }
        else{
            j++;
            ptr1=L->suiv->position;
        }
    }
    return j;
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
    while(tmp != NULL) // On continue est on supprime si on trouve l'element
    {
        if (tmp->position == valeur)
        {
            previous->suiv = tmp->suiv;
            free(tmp);
            return (list);
        }
        previous = tmp; // pour se souvenir dans la prochaine iteration du precedent
        tmp = tmp->suiv;
    }
    return list;
}

void retournPions(char *suite[3],  Move *Liste, Move *L1, Move *L2){
    supprimerElement(listAdverse(Liste, L1, L2), suite);
    insTT(Liste, creatMaillon(Liste->joueur,suite));
}

void verifAllie(char rec[3], char rep[3], Move *Liste, Move *LN, Move *LB, int pre, parametres *jeu)
{
    char recl[3];
    recl[1] = rec[1];
    char suite[3]; 
    suite[0] = rec[0];
    suite[1] = rec[1];
    // Ligne à droite
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
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1; // C'est ici et les lignes similaires en dessous la fin des vérifs stv y mettre tes lignes
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] + 1;
                    }
                }
            }
        }
    }
    // Ligne à gauche
    else if(rec[0] == (rep[0] - 1) && rec[1] == (rep[1])){
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] - i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] - 1;
                    }
                }
            }
        }
    }
    // Colonne dessus
    else if(rec[0] == (rep[0]) && rec[1] == (rep[1] - 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[1] = rec[1] - i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[1] = suite[1] - 1;
                    }
                }
            }
        }
    }
    // Colonne dessous
    else if(rec[0] == (rep[0]) && rec[1] == (rep[1] + 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[1] = rec[1] + i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[1] = suite[1] + 1;
                    }
                }
            }
        }
    }
    // Diagonale en haut à gauche
    else if(rec[0] == (rep[0] - 1) && rec[1] == (rep[1] - 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] - i;
            recl[1] = rec[1] - i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] - 1;
                        suite[1] = suite[1] - 1;
                    }
                }
            }
        }
    }
    // Diagonale en haut à droite
    else if(rec[0] == (rep[0] + 1) && rec[1] == (rep[1] - 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] + i;
            recl[1] = rec[1] - i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] + 1;
                        suite[1] = suite[1] -1;
                    }
                }
            }
        }
    }
    // Diagonale en bas à gauche
    else if(rec[0] == (rep[0] - 1) && rec[1] == (rep[1] + 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] - i;
            recl[1] = rec[1] + i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] - 1;
                        suite[1] = suite[1] + 1;
                    }
                }
            }
        }
    }
    // Diagonale en bas à droite
    else if(rec[0] == (rep[0] + 1) && rec[1] == (rep[1] + 1)){
        for (int i = 1; i < 8; i++)
        {
            recl[0] = rec[0] + i;
            recl[1] = rec[1] + i;
            if (pre == 0)
            {
                printf("position impossible");
                break;
            }
            else
            {
                if(estDans(recl, Liste)){
                    insTT(Liste, creatMaillon(Liste->joueur, rep));
                    Liste->suiv=rep;
                    jeu->tourJoueur = (jeu->tourJoueur % 2) + 1;
                    while(strcmp(suite, recl) != 0){
                        retournPions(suite, Liste, LN, LB);
                        suite[0] = suite[0] + 1;
                        suite[1] = suite[1] + 1;
                    }
                }
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



