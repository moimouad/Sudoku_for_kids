#include "includes.h"

/* le Main , c'est la ou il y'as la page du menu , ainsi que l'initialisation
des outils necessaire dans le jeu comme SDL */

int main(int argc, char *argv[]){

    SDL_Surface *ecran = NULL , *Menu = NULL , *NewGame = NULL , *LoadGame = NULL , *Score = NULL
    ,*NewGame_souris = NULL , *LoadGame_souris = NULL , *Score_souris = NULL; // Le pointeur qui va stocker les surfaces .
    SDL_Rect PositionMenu , PositionNewGame ,PositionLoadGame , PositionScore ; // La position des surface sur l'ecran
    SDL_Event event;

    int continuer = 1,jouer,temps=0;

    // La declaration des tableaux et l'allocation de la memoire
    int** MatriceSudoku; // la matrice qui va contenir le sudoku
    int** Inchangables;  // La matrice qi vas contenir les valeurs qui sont chanjables ou pas

    MatriceSudoku=malloc(4*sizeof(int));
	for(int i=0; i<4; i++) {
		MatriceSudoku[i]=malloc(4*sizeof(int));
	}

	Inchangables=malloc(4*sizeof(int*));
	for(int i=0; i<4; i++) {
		Inchangables[i]=malloc(4*sizeof(int));
	}


    PositionMenu.x = 0;
    PositionMenu.y = 0;

    PositionNewGame.x = 300;
    PositionNewGame.y = 200;

    PositionLoadGame.x = 300;
    PositionLoadGame.y = 300;

    PositionScore.x = 300;
    PositionScore.y = 400;


    FMOD_SYSTEM *system;
    FMOD_SOUND *click;


    /* Création et initialisation d'un objet système (audio) */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* Chargement du son et vérification du chargement */
    FMOD_System_CreateSound(system, "sound/click.wav", FMOD_CREATESAMPLE, 0, &click);

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL .


    SDL_WM_SetCaption("Sudoku", NULL); // Le titre de la fenêtre .

    ecran = SDL_SetVideoMode(MAIN_LARGEUR, MAIN_HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); //  d'ouvrir La fenêtre
    for (;;){
        int a = Identification(ecran) ;    // le Passage vers la page du Mot de passe
        if(a == 1){                        // tant que le mot de passe est faus , il reste dans la page de l'identification
            break ;
        }
        else if (a == 2){
            goto Fin  ;                      // dans la page de l'identification , si il ferme la feunetre , il sort du jeu
        }
    }

    // La phase de l'Uploid des images

    Menu = SDL_LoadBMP("image/menu3.bmp");
    NewGame = IMG_Load("image/new.png");
    LoadGame = IMG_Load("image/load.png");
    Score = IMG_Load("image/score.png") ;
    NewGame_souris = IMG_Load("image/new_souris.png");
    LoadGame_souris = IMG_Load("image/load_souris.png");
    Score_souris = IMG_Load("image/score_souris.png") ;

    Debut :

    // Affichage des image du menu est des bouttons

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(Menu, NULL, ecran, &PositionMenu);
    SDL_BlitSurface(NewGame,NULL,ecran,&PositionNewGame) ;
    SDL_BlitSurface(LoadGame,NULL,ecran,&PositionLoadGame) ;
    SDL_BlitSurface(Score,NULL,ecran,&PositionScore) ;

    SDL_Flip(ecran);    // actualiser l'ecran

    while (continuer)
    {
        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                        continuer = 0;
                        break;
                }
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionNewGame,event.button.x,event.button.y)){
                    /* On charge la page du New game lorcqu'on clique sur le boutton "New game" */
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    do {
                        temps = SDL_GetTicks(); // l'enregistrement du temps du debut de la partie
                        for (int i = 0 ; i < temps/100 ; i++){
                            rand();  // pour que le programme ne donne pas les meme valeur a la premier fois , j'initialise la fct Rand
                        }
                        player a ;
                        jouer = StartGame(ecran,MatriceSudoku,Inchangables,temps,1,a);
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    }while (jouer);
                    goto Debut;
                }
                if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionLoadGame,event.button.x,event.button.y)){
                        /* On charge la page du Load game lorcqu'on clique sur le boutton "Load game" */
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                        temps = SDL_GetTicks();
                        LoadTheGame(ecran,MatriceSudoku,Inchangables,temps);
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);

                    goto Debut;
                }
                if (event.button.button == SDL_BUTTON_LEFT && IsMouseInBoutton(PositionScore,event.button.x,event.button.y)){
                    /* On charge la page du score lorcqu'on clique sur le boutton "score" */
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    HightScore(ecran);
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    goto Debut;
                }
                if (event.button.button == SDL_BUTTON_LEFT && (   event.button.y >= 100 && event.button.y <= 200  && event.button.x >= 460  && event.button.x <= 600 )){
                    /* On charge la page du "a propos" lorcqu'on clique sur la zone de "About us" */
                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                    about_us( ecran);
                    goto Debut;
                }
                break;

                /* la phase responsable de l'animation des boutons lorcqu'on mis la souris sur un boutons */
            case SDL_MOUSEMOTION:
                if (IsMouseInBoutton(PositionLoadGame,event.button.x,event.button.y)) {
                        SDL_BlitSurface(LoadGame_souris,NULL,ecran,&PositionLoadGame) ;
                        SDL_Flip(ecran);
                }
                else if (IsMouseInBoutton(PositionNewGame,event.button.x,event.button.y)) {
                        SDL_BlitSurface(NewGame_souris,NULL,ecran,&PositionNewGame) ;
                        SDL_Flip(ecran);
                }
                else if (IsMouseInBoutton(PositionScore,event.button.x,event.button.y)) {
                        SDL_BlitSurface(Score_souris,NULL,ecran,&PositionScore) ;
                        SDL_Flip(ecran);
                }
                else {
                    goto Debut;
                }
                break ;
            break;
        }
    }

    Fin :
    SDL_FreeSurface(Menu); /* On libère la surface */
    SDL_FreeSurface(NewGame);
    SDL_FreeSurface(LoadGame);
    SDL_FreeSurface(Score);
    SDL_FreeSurface(NewGame_souris);
    SDL_FreeSurface(LoadGame_souris);
    SDL_FreeSurface(Score_souris);

    FMOD_Sound_Release(click);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    SDL_Quit(); // Arrêt de la SDL
    return 0; // Fermeture du programme

}

/* c'est la fonction qui detecte si la souris est sur un bouton ou pas ! */

int IsMouseInBoutton(SDL_Rect bouton , int x , int y){
    /* c'est la fct responsable de tester si on le joueur a cliquer sur un boutton ou pas */
    if (   y >= bouton.y
        && y <= bouton.y + BOUTON_HAUTEUR
        && x >= bouton.x
        && x <= bouton.x + BOUTON_LARGEUR)
        return 1;
    return 0;
}

/* c'est la fct responsable de la securiter du sudoku par un mot de passe */

int Identification(SDL_Surface* ecran){

    SDL_Surface *PassWordPage = NULL ,*texte = NULL ;
    SDL_Rect PositionPasseWordPage ,position;
    SDL_Event event ;
    int continuer = 1;

    char PW[20] = "",PWA[20] = "";

    TTF_Init();

    PositionPasseWordPage.x = 0 ;
    PositionPasseWordPage.y = 0 ;
    position.x = 350;
    position.y = 270;

    PassWordPage = SDL_LoadBMP("image/pw.bmp");

    TTF_Font *police = NULL;
    SDL_Color couleurB = {255, 255, 255};
    police = TTF_OpenFont("font/font2.ttf", 50);
    while (continuer && strlen(PW)< 16 )
    {

        texte = TTF_RenderText_Blended(police, PWA , couleurB);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(PassWordPage, NULL, ecran, &PositionPasseWordPage);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_Flip(ecran);


        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                return 2 ;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    // ici la definition de chaque touche et sa fonctionnaliter
                    case SDLK_RETURN:
                        if (strcmp(PASSWORD,PW)==0){
                            TTF_CloseFont(police);
                            TTF_Quit();
                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(PassWordPage);
                            return 1 ;
                        }
                        else {
                            continuer = 0 ;
                        }
                        break;
                    case SDLK_BACKSPACE:
                        if (strlen(PW)){
                            PW[strlen(PW)-1] = '\0' ;
                            PWA[strlen(PWA)-1] = '\0' ;
                        }
                        break ;
                    case SDLK_q:
                        strcat(PW,"a");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_b:
                        strcat(PW,"b");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_c:
                        strcat(PW,"c");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_d:
                        strcat(PW,"d");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_e:
                        strcat(PW,"e");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_f:
                        strcat(PW,"f");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_g:
                        strcat(PW,"g");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_h:
                        strcat(PW,"h");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_i:
                        strcat(PW,"i");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_j:
                        strcat(PW,"j");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_k:
                        strcat(PW,"k");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_l:
                        strcat(PW,"l");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_SEMICOLON:
                        strcat(PW,"m");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_n:
                        strcat(PW,"n");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_o:
                        strcat(PW,"o");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_p:
                        strcat(PW,"p");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_a:
                        strcat(PW,"q");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_r:
                        strcat(PW,"r");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_s:
                        strcat(PW,"s");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_t:
                        strcat(PW,"t");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_u:
                        strcat(PW,"u");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_v:
                        strcat(PW,"v");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_z:
                        strcat(PW,"w");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_x:
                        strcat(PW,"x");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_y:
                        strcat(PW,"y");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_w:
                        strcat(PW,"z");
                        strcat(PWA,"*");
                        break ;
                    case SDLK_SPACE:
                        strcat(PW," ");
                        strcat(PWA,"*");
                        break ;

                }
            break;

        }
    }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_FreeSurface(PassWordPage);
    return 0 ;
}

 // la fonction qui affiche la page du About Us

void about_us(SDL_Surface* ecran){

    SDL_Surface *ScorePage = NULL ;
    SDL_Rect PositionScorePage;
    SDL_Event event ;

    int continuer = 1;


    PositionScorePage.x = 0 ;
    PositionScorePage.y = 0 ;


    ScorePage = SDL_LoadBMP("image/about_us.bmp");



    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(ScorePage, NULL, ecran, &PositionScorePage);
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

    SDL_FreeSurface(ScorePage);


}
