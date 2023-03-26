#include "main.h"
         


int main(int argc, char **argv)
{
    Move* lst_pions = NULL;
    int i=0;

    SDL_Thread* Thread = SDL_CreateThread(Display, "Affichage", lst_pions);

    while(i<5)
    {
        printf("Ca marche ?\n");
        sleep(3);
        i++;
    }
    SDL_WaitThread(Thread, NULL);

    return 0;

    // Main de Jade
    // affichQua();
    // //rempQua();
    // rempTab();



    // Main de Manon
    // - débug de l'initialisation du jeu partie events ----------------------------------------
    /* on n'en a pas vraiment besoin, dans les autres fonctions du main. 
       Tu peux l'initialiser dans la fonction directement */
    // char rep[3]; 
    // Move *move=NULL; // pourquoi faire ?
    // char pion[6]; // pourquoi faire ?
    
    // respectRegles(rep);

    // // a quoi sert ce switch ?
    // switch (move->joueur)
    // {
    //     case 1 :
    //         strcpy(pion, "noir");
    //         break;
    //     case 2 :
    //         strcpy(pion, "blanc");
    //         break;
    //     default :
    //         printf("Aucune couleur a été attribuée !\n");   
    // }


    // Main de Latifa
    // - débug de la gestion d'historique de coups ---------------------------------------------
    // Move *L, *moves, *actuel;
    // int choix=0 , var1=0;
    // char var2[3];
    // L=NULL;
    // actuel=NULL;
    // while (choix != 5){
    //     printf("\nMenu :\n");
    //     printf("1. Ajouter un coup joué\n");
    //     printf("2. Se déplacer vers le coup précédent\n");
    //     printf("3. Se déplacer vers l'avant\n");
    //     printf("4. Afficher l'historique des coups joués\n");
    //     printf("5. Quitter\n");
    //     printf("Choix : ");
    //     scanf("%d", &choix);
    //     printf("\n");

    //     switch (choix){
    //         case 1:
    //             if (actuel!=NULL){
    //                 if(actuel->suiv!=NULL){
    //                     supprimCoupApres (actuel);
    //                 }
    //                 printf("\nJoueur (1 pour noir ou 2 pour blanc):");
    //                 scanf("%d", &var1);
    //                 printf("\nQuel est la position du joueur ?:");
    //                 scanf("%s", var2);
    //                 moves=creatMaillon(var1, var2);
    //                 L = insTT(L, moves);
    //                 actuel = moves;
    //             }
    //             else if (actuel==NULL){
    //                 if(L==NULL){
    //                     printf("\nJoueur (1 pour noir ou 2 pour blanc):");
    //                     scanf("%d", &var1);
    //                     printf("\nQuel est la position du joueur ?:");
    //                     scanf("%s", var2);
    //                     moves=creatMaillon(var1, var2);
    //                     L = insTT(L, moves);
    //                     actuel = moves;
    //                 }
    //                 else if (L!=NULL){
    //                     printf("\nJoueur (1 pour noir ou 2 pour blanc):");
    //                     scanf("%d", &var1);
    //                     printf("\nQuel est la position du joueur ?:");
    //                     scanf("%s", var2);
    //                     moves=creatMaillon(var1, var2);
    //                     actuel=moves;
    //                     moves->suiv=L;
    //                     L=moves;
    //                     moves->suiv->prec=moves;
    //                     supprimCoupApres(actuel);
    //                 }
    //             }
    //             break;
    //         case 2:
    //             actuel=deplacArriere(actuel);
    //             if (actuel!=NULL) printf("Voici le coup précédent : %s", actuel->position);
    //             else{
    //                 printf("Liste vide!\n");
    //             }
    //             break;
    //         case 3:
    //             actuel=deplacAvant(actuel,L);
    //             if (actuel!=NULL) printf("Vous êtes revenu au coup : %s\n", actuel->position);
    //             else{
    //                 printf("Vous êtes à votre dernier coup!\n");
    //             }
    //             break;
    //         case 4:
    //             printMoveHistory(L,actuel);
    //             break;
    //         case 5:
    //             printf("Au revoir !\n");
    //             break;
    //         default:
    //             printf("Choix invalide, veuillez entrer une option valide.\n");
    //     }
    // }
    // return 0;
}