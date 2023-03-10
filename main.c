#include "main.h"


int main(int argc, char **argv)
{
    char rep[3];
    Move *move=NULL;
    char pion[6];
    respectRegles(rep);
    switch (move->joueur){
        case 1 :
            strcpy(pion, "noir");
            break;
        case 2 :
            strcpy(pion, "blanc");
            break;
        default :
            printf("Aucune couleur a été attribuée !\n");        
    }
    return 0;
}