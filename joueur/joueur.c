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
