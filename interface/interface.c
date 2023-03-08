#include "interface.h"

void affichQua (void)
{
    printf(" Bienvenu sur Othello ");
   
    printf("\n_________________________\n");
    printf("|a1|b1|c1|d1|e1|f1|g1|h1|\n");
    printf("_________________________\n");
    printf("|a2|b2|c2|d2|e2|f2|g2|h2|\n");
    printf("_________________________\n");
    printf("|a3|b3|c3|d3|e3|f3|g3|h3|\n");
    printf("_________________________\n");
    printf("|a4|b4|c4|d4|e4|fs4|g4|h4|\n");
    printf("_________________________\n");
    printf("|a5|b5|c5|d5|e5|f5|g5|h5|\n");
    printf("_________________________\n");
    printf("|a6|b6|c6|d6|e6|f6|g6|h6|\n");
    printf("_________________________\n");
    printf("|a7|b7|c7|d7|e7|f7|g7|h7|\n");
    printf("_________________________\n");
    printf("|a8|b8|c8|d8|e8|f8|g8|h8|\n");
    printf("_________________________\n");
    


}

void rempQua (void)
{
    char nom1[20];
    char nom2[20];
    char c[2];
    char x[1];
    char y[1];
    int a1=0;

    printf("\nJoueur 1 rentrez votre pseudo :\n");
    scanf("%s", nom1);
    printf("Joueur 2, rentrez votre pseudo :\n");
    scanf("%s", nom2);

    printf("\n%s quelle colonne voulez-vous modifier ? \n", nom1);
    scanf("%s",y);
    while(y<1 | y>8)
    {
        printf("\n%s, cette colonne n'existe pas ! quelle colonne voulez-vous modifier ? \n", nom1);
        scanf("%s",y);
    }
    
    printf("\n%s quelle ligne voulez-vous modifer ? \n", nom1);
    scanf("%s",x);

    while(strlen(c)!=2)
    {
        printf("case inexistante, veuillez chosir une case du tableau\n");
        printf("Quelle case voulez modifier ? \n");
        scanf("%s",c);
    }
    
    printf("Que voulez vous mettre dans %s ?\n", c);
    scanf("%d", &a1);
    while()
   

    printf("\n_________________________\n");
    printf("|%d |b1|c1|d1|e1|f1|g1|h1|\n",a1);
    printf("_________________________\n");
    printf("|a2|b2|c2|d2|e2|f2|g2|h2|\n");
    printf("_________________________\n");
    printf("|a3|b3|c3|d3|e3|f3|g3|h3|\n");
    printf("_________________________\n");
    printf("|a4|b4|c4|1 |2 |f4|g4|h4|\n");
    printf("_________________________\n");
    printf("|a5|b5|c5|2 |1 |f5|g5|h5|\n");
    printf("_________________________\n");
    printf("|a6|b6|c6|d6|e6|f6|g6|h6|\n");
    printf("_________________________\n");
    printf("|a7|b7|c7|d7|e7|f7|g7|h7|\n");
    printf("_________________________\n");
    printf("|a8|b8|c8|d8|e8|f8|g8|h8|\n");
    printf("_________________________\n");
    

}

int main(void)
{
    affichQua();
    rempQua();

}