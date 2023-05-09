#include "joueur.h"

//pour debug
// parametres configPlayers(parametres jeu)
// {
//     char start[4];
//     printf("Souhaitez-vous jouer à 1 joueur ou 2 ?\n tapez 1 pour un joueur ou 2 pour 2 joueurs\n");
//     viderBuffer();
//     scanf("%d", &(jeu.nbJoueurs));
//     switch (jeu.nbJoueurs)
//     {
//         case 1 : 
//             printf("Choisissez la difficulté de l'IA : rentrez un nombre entre 1 et 10\n");
//             viderBuffer();
//             scanf("%d", &(jeu.lvlOrdi));
//             printf("Voulez-vous commencer en premier ?  Tapez Oui ou Non : ");
//             viderBuffer();
//             scanf("%s", start);
//             if (strcmp(start, "Oui") == 0 || strcmp(start,"oui") == 0)
//             {
//                 jeu.tourJoueur = 1;
//             }
//             else 
//             {
//                 jeu.tourJoueur = 2;
//             }
//             break;
//         case 2 : 
//             jeu.lvlOrdi = 0;
//             jeu.tourJoueur = 1;
//             break;
//         default : 
//             printf("Ceci n'est pas une réponse correcte\n");
//     }
//     return jeu;
// }

void configPlayer(int x, int y)
{
    if(x>=410 && x<=600 && y>=255 && y<330)
    {
        printf("coucou");
        SDL_LockMutex(mutexJ); 
        jeu->nbJoueurs = 1;
        SDL_UnlockMutex(mutexJ);
    }

    else if(x>=410 && x<=600 && y>=455 && y<527)
    {
        printf("coucou");
        SDL_LockMutex(mutexJ); 
        jeu->nbJoueurs = 2;
        SDL_UnlockMutex(mutexJ);
    }
}





// Move* tourJoueur(parametres* jeu)
// {
//     // initialisation action joueurs
//     char* rep = NULL; 
//     rep = malloc(sizeof(char) * 3);




//     switch(jeu->nbJoueurs)
//     {
//         case 1:
//             if (jeu->tourJoueur == 1)
//             {
//                 rep = demandeJoueur(rep);
//             }
//             else if (jeu->tourJoueur == 2)
//             {
//                 //rep = demandeIA(rep, jeu);
//             }
//             break;

//         case 2:
//             rep = demandeJoueur(rep);
//             break;

//         default:
//             printf("Erreur dans le nombre de joueurs\n");
//     }

//     Move* maillon = creatMaillon(jeu->tourJoueur, rep);
//     printf("Le joueur %d joue en %s \n", jeu->tourJoueur, maillon->position);

//     return maillon;
// }


// char* demandeJoueur(char* rep)
// {
//     while (strlen(rep) != 2)
//     {
//         printf("Quel est la position du joueur : ");
//         viderBuffer();
//         fgets(rep, 3*sizeof(char), stdin);

//         if (strlen(rep) != 2)
//         {
//             printf("La réponse n'est pas conforme...\n");
//         }
//     }
//     return rep;
// }