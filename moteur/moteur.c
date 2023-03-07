#include "moteur.h"


void respectRegles(){
    char rep[3];
    char *listpos[10]; //tableau regroupant toutes les positions des pions 
    int pre = 0; // présent dan sla liste
    printf("Ou souhaitez-vous placer votre pion ?\n");
    scanf("%s", rep);
    while(strlen(rep)!=2){
        printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
        scanf("%s", rep);
    }
    printf("%ld\n", strlen(listpos));
    if((rep[0]>=97 && rep[0]<=104) && (rep[1]>=49 && rep[1]<=56)){
        printf("OK\n");
        for(int i=0; i <= strlen(listpos); i++){
            printf("%s", listpos[i]);
            if(listpos[i]==rep){
                printf("yey\n");
                pre = 1;
            }
        }
        if(pre == 1){
            printf("Position impossible car la case est déjà occupée\n");
        }
        else{
            printf("OK !\n");
            listpos[strlen(listpos)]=rep;
        }
    }
    else{
        printf("Ceci ne correspond pas à une case du plateau !\n");
    }
}


int main(){
    respectRegles();
    return 0;
}