#include "interface.h"


void affichQua (void)
{
    printf(" \nBienvenu sur Othello ");
   
    printf("\n_________________________\n");
    printf("|a1|b1|c1|d1|e1|f1|g1|h1|\n");
    printf("_________________________\n");
    printf("|a2|b2|c2|d2|e2|f2|g2|h2|\n");
    printf("_________________________\n");
    printf("|a3|b3|c3|d3|e3|f3|g3|h3|\n");
    printf("_________________________\n");
    printf("|a4|b4|c4|d4|e4|f4|g4|h4|\n");
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



Move *initAction()
{
    Move *moves =NULL;
    moves=(Move*)malloc(sizeof(Move));
    if(moves == NULL){
        printf("\nAllocation impossible");
    }
    else {
        printf ("\nJoueur qui a joué le coup (1 ou 2):");
        scanf ("%d", &moves->joueur);
        printf ("\nPosition du joueur:");
        scanf ("%s",moves->position);
        while(strlen(moves->position)!=2)
        {
            printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
            scanf("%s", moves->position);
        }

        if((moves->position[0]>=97 && moves->position[0]<=104) && (moves->position[1]>=49 && moves->position[1]<=56))
        {
            printf("OK\n");
        }
        else{
            printf("Ceci ne correspond pas à une case du plateau !\n");
        }
        
        moves->suiv = NULL;
    }
    return moves;
}





Move * rempTab2 (char val[8][8])
{
    Move * move=NULL;
    Move * L=NULL;
    int perso=1;
    for(int i=0; i<5;i++)
    {
        initAction();
        //insTT(L, move);
    }
    
    while(L!=NULL)
    {
        for(int j=0;j<64;j++)
        {
            for(int k=0; k<64;k++)
            {
                if(strcmp(move->position,&val[k][j])==0)
                {
                    if(move->joueur == perso)
                    {
                        val[k][j]=1;
                    }
                    else
                    {
                        val[k][j]=2;
                    }
                }   

            }
            
        }
    }
    return L;
}

void rempTab (void)
{
   
    char val[8][8];
    rempTab2 (val);
    for(int j=0;j<=7;j++)
    {
        for(int i=0;i<=7;i++)
        {
            val[j][i]=' ';
        }

    }
    val[3][3]='1';
    val[4][4]='1';
    val[4][3]='2';
    val[3][4]='2';
    
    
    printf("\n_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[0][0], val[0][1],val[0][2],val[0][3],val[0][4],val[0][5],val[0][7],val[0][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[1][0], val[1][1],val[1][2],val[1][3],val[1][4],val[1][5],val[1][7],val[1][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[2][0], val[2][1],val[2][2],val[2][3],val[2][4],val[2][5],val[2][7],val[2][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[3][0], val[3][1],val[3][2],val[3][3],val[3][4],val[3][5],val[3][7],val[3][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[4][0], val[4][1],val[4][2],val[4][3],val[4][4],val[4][5],val[4][7],val[4][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[5][0], val[5][1],val[5][2],val[5][3],val[5][4],val[5][5],val[5][7],val[5][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[6][0], val[6][1],val[6][2],val[6][3],val[6][4],val[6][5],val[6][7],val[6][7]);
    printf("_________________________\n");
    printf("|%c |%c |%c |%c |%c |%c |%c |%c |\n",val[7][0], val[7][1],val[7][2],val[7][3],val[7][4],val[7][5],val[7][7],val[7][7]);
    printf("_________________________\n");
}







int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    TTF_Font *font;
    SDL_Color color = { 255, 255, 255 };
    int quit = 0;
    
    // Initialisation de SDL2
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    // Création de la fenêtre
    window = SDL_CreateWindow("OTHELO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Chargement de la police d'écriture
    font = TTF_OpenFont("Desktop/nice_sugar/Nice Sugar.ttf", 32);

    // Création de la surface de rendu du texte
    surface = TTF_RenderText_Solid(font, "Bonjour, comment ça va ?", color);

    // Création de la texture à partir de la surface de rendu du texte
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Boucle principale
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }
         // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);

        // Affichage de la texture contenant le texte
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        
        // Affichage du rendu à l'écran
        SDL_RenderPresent(renderer);
    }
    
    // Libération des ressources
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}

