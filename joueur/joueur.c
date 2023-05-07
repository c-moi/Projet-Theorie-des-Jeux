#include "joueur.h"


char* configPlayers(Move *move, char rep[3])
{
    int choix;
    int lvl;
    move->joueur=1;
    printf("Souhaitez-vous jouer à 1 joueur ou 2 ?\n tapez 1 pour un joueur ou 2 pour 2 joueurs\n");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : 
            printf("Choisissez la difficulté de l'IA : rentrez un nombre entre 1 et 10\n");
            scanf("%d", &lvl);
            rep = lancerPartie(move, rep);
            break;
        case 2 :  
            rep = lancerPartie(move, rep);
            break;
        default : 
            printf("Ceci n'est pas une réponse correcte\n");
            rep = "0";
    }
    return rep;
}

char* lancerPartie(Move *move, char rep[3])
{
        printf("Lancement de la partie...");
        printf("Joueur %d ou souhaitez-vous placer votre pion ?\n", move->joueur);
        scanf("%s", rep);
        return rep;
}









// char* configPlayers(Move *move, char rep[3]){
//     int choix;
//     int diff;
//     move->joueur=1;
//     printf("Souhaitez-vous jouer à 1 joueur ou 2 ?\n tapez 1 pour un joueur ou 2 pour 2 joueurs\n");
//     scanf("%d", &choix);
//     switch (choix){
//         case 1 : 
//             printf("Choisissez la difficulté de l'IA : rentrez un nombre entre 1 et 10\n");
//             scanf("%d", &diff);
//             rep = lancerPartie(move, rep);
//             break;
//         case 2 :  
//             rep = lancerPartie(move, rep);
//             break;
//         default : 
//             printf("Ceci n'est pas une réponse correcte\n");
//             rep = "0";
//     }
//     return rep;
// }

// char* lancerPartie(Move *move, char rep[3]){
//         printf("Lancement de la partie...");
//         printf("Joueur %d ou souhaitez-vous placer votre pion ?\n", move->joueur);
//         scanf("%s", rep);
//         return rep;
// }


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
                rep = demandeIA(rep, jeu);
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