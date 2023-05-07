#include "joueur.h"


parametres configPlayers(parametres jeu)
{
    char start[4];
    printf("Souhaitez-vous jouer à 1 joueur ou 2 ?\n tapez 1 pour un joueur ou 2 pour 2 joueurs\n");
    scanf("%d", &(jeu.nbJoueurs));
    switch (jeu.nbJoueurs)
    {
        case 1 : 
            printf("Choisissez la difficulté de l'IA : rentrez un nombre entre 1 et 10\n");
            scanf("%d", &(jeu.lvlOrdi));
            printf("Voulez-vous commencer en premier ?  Tapez Oui ou Non : ");
            scanf("%s", start);
            if (strcmp(start, "Oui") == 0 || strcmp(start,"oui") == 0)
            {
                jeu.tourJoueur = 1;
            }
            else 
            {
                jeu.tourJoueur = 2;
            }
            break;
        case 2 : 
            jeu.lvlOrdi = 0;
            jeu.tourJoueur = 1;
            break;
        default : 
            printf("Ceci n'est pas une réponse correcte\n");
    }
    return jeu;
}






Move* tourJoueur(parametres* jeu)
{
    // initialisation action joueurs
    char* rep = NULL; 
    rep = malloc(sizeof(char) * 3);




    switch(jeu->nbJoueurs)
    {
        case 1:
            if (jeu->tourJoueur == 1)
            {
                demandeJoueur(&rep);
            }
            else if (jeu->tourJoueur == 2)
            {
                //rep = demandeIA(rep, jeu);
            }
            break;

        case 2:
            demandeJoueur(&rep);
            break;

        default:
            printf("Erreur dans le nombre de joueurs\n");
    }

    Move* maillon = creatMaillon(jeu->tourJoueur, rep);
    printf("Le joueur %d joue en %s \n", maillon->joueur, maillon->position);

    return maillon;
}


void demandeJoueur(char** rep)
{
    clean_stdin();
    while (strlen(*rep) != 2)
    {
        printf("Quel est la position du joueur : ");
        fgets(*rep, 3*sizeof(char), stdin);

        if (strlen(*rep) != 2)
        {
            printf("La réponse n'est pas conforme...\n");
        }
    }
}

void clean_stdin(void)
{
    int c;
 
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}