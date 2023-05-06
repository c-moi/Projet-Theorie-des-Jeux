#include "interface.h"


// SDL_Renderer *creercroix(SDL_Renderer *rend,int x2, int y2)
// {
//     int size = 50;
//     SDL_RenderDrawLine(rend, x2 - size, y2 - size, x2 + size, y2 +size);
//     SDL_RenderDrawLine(rend, x2 -size , y2 + size, x2 + size , y2 - size);
// }

void Display(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    TTF_Font *font;
    //SDL_Color color = {255, 255, 255};
    int quit = 0;

    //Initialisation test maj
    Move* printed_SDL = NULL;
    printed_SDL = listeG;

    SDL_Thread* Debug = SDL_CreateThread(debug, "Débug", NULL);

    // Initialisation de SDL2
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    // Création de la fenêtre
    window = SDL_CreateWindow("OTHELLO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 590, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

    // // Chargement de la police d'écriture
    font = TTF_OpenFont("/Users/jade/Desktop/ALgo/Projet_Algo_2/Projet-Theorie-des-Jeux/nice_sugar/Nice Sugar.ttf", 27);
        if (!font) 
         {
            printf("Erreur lors du chargement de la police : %s", TTF_GetError());
            exit(EXIT_FAILURE);
        }

    // Charger l'image du plateau d'échec
    SDL_Surface* imtableau = IMG_Load("/Users/jade/Desktop/Algo/Projet_Algo_2/Projet-Theorie-des-Jeux/plateau_img/plateaurose.png");
    if (!imtableau) 
        {
            printf("Erreur image nulle ");
            exit(EXIT_FAILURE);
        }
    
    // Charger l'image des boutons
    SDL_Surface* boutonOff = IMG_Load("/Users/jade/Desktop/Algo/Projet_Algo_2/Projet-Theorie-des-Jeux/boutonOff/boutonOff.png");
    if (!boutonOff) 
        {
            printf("Erreur image nulle ");
            exit(EXIT_FAILURE);
        }
    
    // Charger l'image des pions BLANCS
    SDL_Surface* pBlanc = IMG_Load("/Users/jade/Desktop/Algo/Projet_Algo_2/Projet-Theorie-des-Jeux/pion/pionBlanc.png");
    if (!pBlanc) 
        {
            printf("Erreur image nulle ");
            exit(EXIT_FAILURE);
        }

    // Charger l'image des pions BLANCS
    SDL_Surface* pNoir = IMG_Load("/Users/jade/Desktop/Algo/Projet_Algo_2/Projet-Theorie-des-Jeux/pion/pionNoir.png");
    if (!pNoir) 
        {
            printf("Erreur image nulle ");
            exit(EXIT_FAILURE);
        }

    // Boucle principale
    while (!quit)
    {
        // if (strcmp(listCpy,listeG)!= 0)
        // {
        //     listCpy = listeG;
        // }
        
        
        
        // // dessin d'un cercle 
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        // int x1 = 275;
        // int y1 = 325;
        // int x3 = 325;
        // int y3 = 275;
        // int radius = 10;
        // int thickness = 1;
        // for (int w = 0; w < radius * 2; w++)
        // {
        //     for (int h = 0; h < radius * 2; h++) 
        //     {
        //         int dx = radius - w; // horizontal offset
        //         int dy = radius - h; // vertical offset
        //         int distance = dx*dx + dy*dy;
        //         if (distance >= (radius - thickness) * (radius - thickness) && distance <= (radius + thickness) * (radius + thickness))
        //         {
        //             SDL_RenderDrawPoint(renderer, x1 + dx, y1 + dy);
        //             SDL_RenderDrawPoint(renderer, x3 + dx, y3 + dy);
        //         }
        //     }
        // }

        // // Dessin d'une croix
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        // int x2=325;
        // int y2=325;
        // int x4=275;
        // int y4=275;
        // int size = 10;
        // SDL_RenderDrawLine(renderer, x2 - size, y2 - size, x2 + size, y2 +size);
        // SDL_RenderDrawLine(renderer, x2 -size , y2 + size, x2 + size , y2 - size);  
        // SDL_RenderDrawLine(renderer, x4 - size, y4 - size, x4 + size, y4 +size);
        // SDL_RenderDrawLine(renderer, x4 -size , y4 + size, x4 + size , y4 - size);

        // //dessin tableau
        // int table[8][8] = {{0}};
        // // Determine the size of each cell in the table
        // int cell_size = 50;
        // // Draw each cell in the table
        // for (int i = 2; i < 10; i++) 
        // {
        //     for (int j = 2; j < 10; j++) 
        //     {
        //         SDL_Rect cell = {j * cell_size, i * cell_size, cell_size, cell_size};
        //         SDL_RenderDrawRect(renderer, &cell);
        //     }
        // }

        


        

        
        // Affichage de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        

        // Création de la surface de rendu du texte
        surface = TTF_RenderText_Solid(font, "Bienvenue sur Othello ", (SDL_Color){255,255,255,255}); 
        // Création de la texture à partir de la surface de rendu du texte
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        // Affichage de la texture contenant le texte
        SDL_Rect destRect = {600, 0, 0, 0};
        SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        

        //Afficher Tableau
        //Afficher la texture
        SDL_Texture* imtexture = SDL_CreateTextureFromSurface(renderer, imtableau);
        // Afficher la surface sur la fenêtre
        SDL_Rect rect = {0, 0, imtableau->w, imtableau->h};
        SDL_QueryTexture(imtexture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, imtexture, NULL, &rect);
        SDL_UpdateWindowSurface(window);

        //Afficher Bouton
        //Afficher la texture
        SDL_Texture* btexture = SDL_CreateTextureFromSurface(renderer, boutonOff);
        // Afficher la surface sur la fenêtre
        SDL_Rect brect = {600, 125, boutonOff->w, boutonOff->h};
        SDL_QueryTexture(btexture, NULL, NULL, &brect.w, &brect.h);
        SDL_RenderCopy(renderer, boutonOff, NULL, &brect);
        SDL_UpdateWindowSurface(window);

        //afficher menu
        // Création de la surface de rendu du texte
        SDL_Surface* msurface = TTF_RenderText_Solid(font, "Menu", (SDL_Color){255,255,255,255}); 
        // Création de la texture à partir de la surface de rendu du texte
        SDL_Texture* mtexture = SDL_CreateTextureFromSurface(renderer, msurface);
        // Affichage de la texture contenant le texte
        SDL_Rect mRect = {600, 125, 0, 0};
        SDL_QueryTexture(mtexture, NULL, NULL, &mRect.w, &mRect.h);
        SDL_RenderCopy(renderer, mtexture, NULL, &mRect);

        
        // Affichage du rendu à l'écran
        SDL_RenderPresent(renderer);

    

        // Gestion des événements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                         "Clic de souris",
                                         "Vous avez cliqué avec le bouton droit de la souris !",
                                         NULL);
                }
            
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    //Afficher la texture
                    SDL_Texture* pbtexture = SDL_CreateTextureFromSurface(renderer, pBlanc);
                    // Afficher la surface sur la fenêtre
                    SDL_Rect pbrect = {x, y, pBlanc->w, pBlanc->h};
                    SDL_QueryTexture(pbtexture, NULL, NULL, &pbrect.w, &pbrect.h);
                    SDL_RenderCopy(renderer, pbtexture, NULL, &pbrect);
                    SDL_UpdateWindowSurface(window);
                    
                    
                    
                    
                }
                break;
            
            }
        }
        

        // réinitialiser  l'écran
        SDL_RenderClear(renderer);
        SDL_FreeSurface(surface);
    }
    exit(0);

    //Libération des ressources
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    SDL_WaitThread(Debug, NULL);

    // je fais juste un test pour te montrer comment ça fonctionne

//     SDL_Window *window = NULL;
//     SDL_Renderer *renderer = NULL;
//     SDL_Event event;

//     SDL_Init(SDL_INIT_VIDEO);

//     window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

//     renderer = SDL_CreateRenderer(window, -1, 0);

//     while(1)
//     {
//         while(SDL_PollEvent(&event))
//         {
//             if(event.type == SDL_QUIT)
//             {
//                 SDL_DestroyRenderer(renderer);
//                 SDL_DestroyWindow(window);
//                 SDL_Quit();

//                 exit(0);
//             }
//         }

//         SDL_RenderClear(renderer);

//         SDL_RenderPresent(renderer);
//     }
}




void aff(Move* liste_debug)
{
    if(liste_debug != NULL)
        {
            while (liste_debug != NULL)
            {
                printf("Liste 2 : %d %s\n", liste_debug->joueur, liste_debug->position);
                liste_debug = liste_debug->suiv;
            }
        }
}



// Partie débug dans terminal
int debug(void* DATA)
{
    Move* printed_term = NULL;

    affichQua();

    SDL_Delay(5000);

    while (1)
    {
        // printf("%s\n", (listCmp(printed_term)) ? "true" : "false");
        // SDL_Delay(2000);
        if (listCmp(printed_term) == false)
        {
            printed_term = listCpy();
            rempTab(printed_term);

            // aff(printed_term);
        }
    }

    return 0;
}

bool listCmp (Move* liste_printed)
{
    Move* tmp = listeG;
    while (tmp != NULL || liste_printed != NULL)
    {
        if (tmp == NULL || liste_printed == NULL)
        {
            return false;
        }
        else
        {
            if (tmp->joueur != liste_printed->joueur)
            {
                if (tmp->position != liste_printed->position)
                {
                    return false;
                }
                else
                {
                    tmp = tmp->suiv;
                    liste_printed = liste_printed->suiv;
                }
            }
            else
            {
                tmp = tmp->suiv;
                liste_printed = liste_printed->suiv;
            }
        }
    }

    return true;
}

Move* listCpy (void)
{
    Move* tmp = listeG;
    Move* Cpyliste = malloc(sizeof(Move));
    Move* tmp2 = Cpyliste;

    while (tmp != NULL)
    {
        tmp2->joueur = tmp->joueur;
        strcpy(tmp2->position, tmp->position);

        if(tmp->suiv != NULL)
            tmp2->suiv = malloc(sizeof(Move));
        else
            tmp2->suiv = NULL;
        
        tmp2->prec = NULL;

        tmp2 = tmp2->suiv;
        tmp = tmp->suiv;
    }

    return Cpyliste;
}


void affichQua(void)
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

// Move *initAction()
// {
//     Move *moves=NULL;
//     moves=(Move*)malloc(sizeof(Move));
//     if(moves == NULL){
//         printf("\nAllocation impossible");
//     }
//     else {
//         printf ("\nJoueur qui a joué le coup (1 ou 2):");
//         scanf ("%d", &moves->joueur);
//         printf ("\nPosition du joueur:");
//         scanf ("%s",moves->position);
//         while(strlen(moves->position)!=2)
//         {
//             printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
//             scanf("%s", moves->position);
//         }
//         if((moves->position[0]>=97 && moves->position[0]<=104) && (moves->position[1]>=49 && moves->position[1]<=56))
//         {
//             printf("OK\n");
//         }
//         else{
//             printf("Ceci ne correspond pas à une case du plateau !\n");
//         }

//         moves->suiv = NULL;
//     }
//     return moves;
// }

// void rempQua(void)
// {
//     char nom1[20];
//     char nom2[20];
//     char c[3];
//     // char x[1];
//     // char y[1];
//     int a1 = 0;

    // ###### Pas sûr de ce que c'est #####

    //     printf("\nJoueur 1 rentrez votre pseudo :\n");
    //     scanf("%s", nom1);
    //     printf("Joueur 2, rentrez votre pseudo :\n");
    //     scanf("%s", nom2);

    //     int pre = 0; // présent dans la liste
    //     printf("Ou souhaitez-vous placer votre pion ?\n");
    //     scanf("%s", c);
    //     while(strlen(c)!=2){
    //         printf("Cela ne correspond pas à un numéro de case, rentrez une lettre suivie d'un chiffre :\n");
    //         scanf("%s", c);
    //     }

    //     if((c[0]>=97 && c[0]<=104) && (c[1]>=49 && c[1]<=56)){
    //         printf("OK\n");
    //     }
    //     else{
    //         printf("Ceci ne correspond pas à une case du plateau !\n");
    //     }

    //     //printf("\n%s quelle colonne voulez-vous modifier ? \n", nom1);
    //     //scanf("%s",y);
    //     //while(y<1 | y>8)
    //     {
    //        // printf("\n%s, cette colonne n'existe pas ! quelle colonne voulez-vous modifier ? \n", nom1);
    //         //scanf("%s",y);
    //     }

    //     // printf("\n%s quelle case voulez-vous modifer ? \n", nom1);
    //     // scanf("%s",c);
    //     // printf("%lu",strlen(c));
    //     // while(strlen(c)!=2)
    //     // {
    //     //     printf("case inexistante, veuillez chosir une case du tableau\n");
    //     //     printf("Quelle case voulez modifier ? \n");
    //     //     scanf("%s",c);
    //     // }

    //     printf("Que voulez vous mettre dans %s ?\n",c );
    //     scanf("%d", &a1);

    //     printf("\n_________________________\n");
    //     printf("|%d |  |c1|d1|e1|f1|g1|h1|\n",a1);
    //     printf("_________________________\n");
    //     printf("|a2|b2|c2|d2|e2|f2|g2|h2|\n");
    //     printf("_________________________\n");
    //     printf("|a3|b3|c3|d3|e3|f3|g3|h3|\n");
    //     printf("_________________________\n");
    //     printf("|a4|b4|c4|1 |2 |f4|g4|h4|\n");
    //     printf("_________________________\n");
    //     printf("|a5|b5|c5|2 |1 |f5|g5|h5|\n");
    //     printf("_________________________\n");
    //     printf("|a6|b6|c6|d6|e6|f6|g6|h6|\n");
    //     printf("_________________________\n");
    //     printf("|a7|b7|c7|d7|e7|f7|g7|h7|\n");
    //     printf("_________________________\n");
    //     printf("|a8|b8|c8|d8|e8|f8|g8|h8|\n");
    //     printf("_________________________\n");
// }

// ##### fin de la partie doute #####

void rempTab (Move* liste)
{
    char* val[8][8];
    rempTab2 (liste, val);

    for(int j=0;j<=7;j++)
    {
        for(int i=0;i<=7;i++)
        {
            if (strlen(val[j][i]) == 2)
            {
                val[j][i]=" ";
            }
        }
    }

    printf("\n_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[0][0], val[0][1],val[0][2],val[0][3],val[0][4],val[0][5],val[0][6],val[0][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[1][0], val[1][1],val[1][2],val[1][3],val[1][4],val[1][5],val[1][6],val[1][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[2][0], val[2][1],val[2][2],val[2][3],val[2][4],val[2][5],val[2][6],val[2][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[3][0], val[3][1],val[3][2],val[3][3],val[3][4],val[3][5],val[3][6],val[3][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[4][0], val[4][1],val[4][2],val[4][3],val[4][4],val[4][5],val[4][6],val[4][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[5][0], val[5][1],val[5][2],val[5][3],val[5][4],val[5][5],val[5][6],val[5][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[6][0], val[6][1],val[6][2],val[6][3],val[6][4],val[6][5],val[6][6],val[6][7]);
    printf("_________________________\n");
    printf("|%s |%s |%s |%s |%s |%s |%s |%s |\n",val[7][0], val[7][1],val[7][2],val[7][3],val[7][4],val[7][5],val[7][6],val[7][7]);
    printf("_________________________\n");
}


void rempTab2 (Move* liste, char* val[8][8])
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            char* var = malloc(sizeof(char)*3);
            sprintf(var, "%c%c", 'a'+i, '1'+j);
            val[i][j] = var;
        }
    }

    if(liste)

    while(liste != NULL)
    {
        for(int j=0; j<8; j++)
        {
            for(int k=0; k<8; k++)
            {
                if(strlen(val[j][k]) == 2 && strcmp(liste->position, val[j][k]) == 0)
                {
                    if(liste->joueur == 1)
                    {
                        char* var = malloc(sizeof(char)*2);
                        var = "1";
                        val[j][k] = var;
                    }
                    else
                    {
                        char* var = malloc(sizeof(char)*2);
                        var = "2";
                        val[j][k] = var;
                    }
                }

            }

        }
        liste = liste->suiv;
    }
}