#include "LoadTheGame.h"

/* c'est la fonction responsable de la page du Load Game , donc on parle de l'importation des sauvgarde depuis les fichiers puis les
afficher , et si le joueur choisi une, le programme assure l,importation du sauvgarde */

int LoadTheGame(SDL_Surface* ecran,int** m, int** v,int temps){
    SDL_Surface *LoadGame = NULL ,*Partie[10]= {NULL} , *BoutonClear = NULL , *BoutonAcc,*BoutonClear_souris = NULL , *BoutonAcc_souris = NULL , *ligne = NULL;
    SDL_Rect PositionLoadGame,PositionPartie[10],PositionSelection[10],PositionClear, PositionAcc;
    SDL_Event event ;
    FILE* file ;
    player Players[10];
    int continuer = 1,j=0;

    PositionLoadGame.x = 0 ;
    PositionLoadGame.y = 0 ;

    PositionClear.x = 575 ;
    PositionClear.y =  25 ;

    PositionAcc.x =  25 ;
    PositionAcc.y =  25 ;

    for (int i = 0 ; i < 10 ; i++ ){
        PositionPartie[i].x = POSITION_X + 25  ;
        PositionPartie[i].y = POSITION_Y + 50*i ;
    }
    for (int i = 0 ; i < 10 ; i++ ){
        PositionSelection[i].x = POSITION_X  ;
        PositionSelection[i].y = POSITION_Y + 50*i ;
    }

    FMOD_SYSTEM *system;
    FMOD_SOUND *click;


    /* Création et initialisation d'un objet système */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* Chargement du son et vérification du chargement */
    FMOD_System_CreateSound(system, "sound/click.wav", FMOD_CREATESAMPLE, 0, &click);






    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurB = {255, 255, 255};
    police = TTF_OpenFont("font/font.ttf", 40);

    print :

    LoadGame = SDL_LoadBMP("image/loadgame2.bmp");
    BoutonClear = IMG_Load("image/clear.png");
    BoutonAcc = IMG_Load("image/acc2.png");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(LoadGame, NULL, ecran, &PositionLoadGame);
    SDL_BlitSurface(BoutonClear, NULL, ecran, &PositionClear);
    SDL_BlitSurface(BoutonAcc, NULL, ecran, &PositionAcc);
    SDL_FreeSurface(LoadGame);
    SDL_FreeSurface(BoutonClear);
    SDL_FreeSurface(BoutonAcc);
    file = fopen("sauvgarde.ensias","rb");
    j = 0 ;

    while (feof(file)==0 && j <11){
        fread(&Players[j], sizeof(player), 1, file);
        j ++ ;
    }
    j--;
    fclose(file);



    for (int i = 0 ; i < j ; i ++){
        Partie[i] = TTF_RenderText_Blended(police, Players[i].name , couleurB);
        SDL_BlitSurface(Partie[i], NULL, ecran, &PositionPartie[i]);
        SDL_FreeSurface(Partie[i]);
    }
    SDL_Flip(ecran);



    while (continuer)
    {


        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionClear,event.button.x,event.button.y)){
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    file = fopen("sauvgarde.ensias","wb");
                    fclose(file);
                    goto print ;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionAcc,event.button.x,event.button.y)){
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    continuer = 0 ;
                }
                else {
                    for (int i = 0 ; i < j; i ++){
                        if (event.button.button == SDL_BUTTON_LEFT && IsMouseInLoad(PositionPartie[i],event.button.x,event.button.y)){
                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                            StartGame(ecran,m,v,temps,0,Players[i]);
                            continuer = 0 ;
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (IsMouseInBoutton(PositionClear,event.button.x,event.button.y)){
                    BoutonClear_souris = IMG_Load("image/clear_souris.png");
                    SDL_BlitSurface(BoutonClear_souris, NULL, ecran, &PositionClear);
                    SDL_Flip(ecran);
                    SDL_FreeSurface(BoutonClear_souris);
                }
                else if (IsMouseInBoutton(PositionAcc,event.button.x,event.button.y)){
                    BoutonAcc_souris = IMG_Load("image/acc2_souris.png");
                    SDL_BlitSurface(BoutonAcc_souris, NULL, ecran, &PositionAcc);
                    SDL_Flip(ecran);
                    SDL_FreeSurface(BoutonAcc_souris);
                }
                else {
                    int a = 1 ;
                    for (int i = 0 ; i < j; i ++){
                        if (IsMouseInLoad(PositionPartie[i],event.button.x,event.button.y)){
                            Partie[i] = TTF_RenderText_Blended(police, Players[i].name , couleurB);
                            SDL_BlitSurface(Partie[i], NULL, ecran, &PositionPartie[i]);
                            ligne =  IMG_Load("image/ligne2.png") ;
                            SDL_BlitSurface(ligne, NULL, ecran, &PositionSelection[i]);
                            SDL_Flip(ecran);
                            SDL_FreeSurface(ligne);
                            SDL_FreeSurface(Partie[i]);
                            a = 0 ;
                        }
                    }

                    if (a) goto print ;}
                break ;

        }
    }
    TTF_CloseFont(police);
    TTF_Quit();

    FMOD_Sound_Release(click);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

}

/* c'est la fonction qui detecte si la souris est sur un bouton ou pas ! */

int IsMouseInLoad(SDL_Rect bouton , int x , int y){
    if (   y >= bouton.y
        && y <= bouton.y + LOAD_HAUTEUR
        && x >= bouton.x
        && x <= bouton.x + LOAD_LARGEUR)
        return 1;
    return 0;
}

