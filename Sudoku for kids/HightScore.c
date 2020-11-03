#include "HightScore.h"

void HightScore(SDL_Surface* ecran){
    SDL_Surface *ScorePage = NULL ,*Partie[10]= {NULL} ,*scoreuser[10] = {NULL}, *BoutonClear = NULL , *BoutonAcc = NULL,*BoutonClear_souris = NULL , *BoutonAcc_souris = NULL;
    SDL_Rect PositionScorePage,PositionPartie[10],Positionscore[10],PositionClear, PositionAcc;
    SDL_Event event ;

    FILE* file ;
    playerscore Players[10];
    int continuer = 1,j=0;

    PositionScorePage.x = 0 ;
    PositionScorePage.y = 0 ;

    PositionClear.x = 575 ;
    PositionClear.y =  25 ;

    PositionAcc.x =  25 ;
    PositionAcc.y =  25 ;

    for (int i = 0 ; i < 10 ; i++ ){
        PositionPartie[i].x = POSITION_X ;
        PositionPartie[i].y = POSITION_Y + 50*i ;
        Positionscore[i].x =  635 ;
        Positionscore[i].y = POSITION_Y + 50*i ;
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

    Tri_score() ;

    print :

        ScorePage = SDL_LoadBMP("image/hightscore2.bmp");
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(ScorePage, NULL, ecran, &PositionScorePage);
        SDL_FreeSurface(ScorePage);





        file = fopen("Hight_Score.ensias","rb");
        j = 0 ;
        while (feof(file)==0 && j <11){
            fread(&Players[j], sizeof(playerscore), 1, file);
            j ++ ;
        }
        j--;
        fclose(file);



        for (int i = 0 ; i < j ; i ++){

            char texte[20]="" ;
            Partie[i] = TTF_RenderText_Blended(police, Players[i].name , couleurB);
            TrasformerTempsEnChar(Players[i].score,texte) ;
            scoreuser[i] = TTF_RenderText_Blended(police, texte , couleurB);
            SDL_BlitSurface(Partie[i], NULL, ecran, &PositionPartie[i]);
            SDL_BlitSurface(scoreuser[i], NULL, ecran, &Positionscore[i]);
            SDL_FreeSurface(Partie[i]);
            SDL_FreeSurface(scoreuser[i]);

        }

        BoutonClear = IMG_Load("image/clear.png");
        BoutonAcc = IMG_Load("image/acc2.png");
        SDL_BlitSurface(BoutonClear, NULL, ecran, &PositionClear);
        SDL_BlitSurface(BoutonAcc, NULL, ecran, &PositionAcc);
        SDL_FreeSurface(BoutonClear);
        SDL_FreeSurface(BoutonAcc);

        SDL_Flip(ecran);





    while (continuer)
    {





        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionClear,event.button.x,event.button.y)){
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    file = fopen("Hight_Score.ensias","wb");
                    fclose(file);
                    goto print ;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionAcc,event.button.x,event.button.y)){
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    continuer = 0 ;
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
                else {goto print ;}
                break ;
        }
    }

    TTF_CloseFont(police);
    TTF_Quit();




    for (int i = 0 ; i < j ; i ++){

    }
    FMOD_Sound_Release(click);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

void Tri_score() {
    int j = 0 ;
    FILE* file ;
    playerscore Players[20],t;
    file = fopen("Hight_Score.ensias","rb");
    j = 0 ;
    while (feof(file)==0 ){
        fread(&Players[j], sizeof(playerscore), 1, file);
        j ++ ;
    }
    j-- ;
    fclose(file);

    int max = 0 , indicemax = 0 ;

    for (int i = 0 ; i<j ; i++){
        max = 0 , indicemax = 0 ;
        for (int k = i ; k < j ; k ++){
            if (Players[k].score > max) {indicemax = k ; max = Players[k].score ; }
        }
        t=Players[i];
        Players[i]=Players[indicemax];
        Players[indicemax] = t ;
    }

    file = fopen("Hight_Score.ensias","wb");
    for (int i = j-1 ; i >= 0 ; i--){
        fwrite(&Players[i],sizeof(playerscore),1,file);
    }
    fclose(file);

}
