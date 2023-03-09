#include "main.h"


int main(int argc, char **argv)
{
    Move *move=NULL;
    char pion[6];
    respectRegles();
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