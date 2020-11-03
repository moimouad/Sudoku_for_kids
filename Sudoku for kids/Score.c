#include "Score.h"

/* c'est la fonction qui assure l'affichage de la page du score , ainsi qu'afficher le score du joueur */

void FctScore(SDL_Surface* ecran,int Temps,char* name){

    SDL_Surface *ScorePage = NULL ,*texte = NULL ;
    SDL_Rect PositionScorePage ,position;
    SDL_Event event ;

    FMOD_SYSTEM *system;
    FMOD_SOUND *click;


    /* Création et initialisation d'un objet système */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* Chargement du son et vérification du chargement */
    FMOD_System_CreateSound(system, "sound/victory.wav", FMOD_CREATESAMPLE, 0, &click);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);

    int Now = SDL_GetTicks();
    int continuer = 1;

    char temps[20] = "";

    TTF_Init();

    PositionScorePage.x = 0 ;
    PositionScorePage.y = 0 ;
    position.x = 500;
    position.y = 275;

    Now -= Temps  ;

    TrasformerTempsEnChar(Now,temps);

    SauvgarderScore(Now,name);

    ScorePage = SDL_LoadBMP("image/scorepage2.bmp");

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("font/font.ttf", 50);
    texte = TTF_RenderText_Blended(police, temps , couleurNoire);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(ScorePage, NULL, ecran, &PositionScorePage);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                continuer = 0;
                break;
        }
    }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(ScorePage);
    SDL_FreeSurface(texte);
    FMOD_Sound_Release(click);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

}

/* puisque le score un entier , donc cette fonction a comme raison transformer ce entier sous la forme suivante :
min : seconde */

void TrasformerTempsEnChar(int Now,char* temps){
    int min = 0 ;

    char sec[2] = "" , minu[2] = "" ;
    Now = Now/1000 ;

    min = (int) Now/60 ;
    Now = Now - 60 * min ;


    sprintf(minu ,"%d", min);
    sprintf(sec ,Now<10 ? "0%d" : "%d", Now);
    if (min == 0) strcat(temps,"0");
    strcat(temps,minu);
    strcat(temps,":");
    if (Now == 0) strcat(temps,"0");
    strcat(temps,sec);
}

/* c'est la fonction qui assure le sauvgarde des score dans un fichier */

void SauvgarderScore(int now,char* name){
    playerscore user ;
    FILE* file ;
    strcpy(user.name, name);
    user.score = now;
    file = fopen("Hight_Score.ensias","ab");
    fwrite(&user,sizeof(playerscore),1,file);
    fclose(file);
}
