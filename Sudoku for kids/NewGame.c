#include "NewGame.h"

/* c'est la fonction Principale dans le jeu . il y'as deux cas dans cette fonction :
soit continuer une sauvgarde soit une nouvelle partie , pour la sauvgarde il rempli le sudoku par le sauvgarde puis donner au joueur
la main pour jouer , sinon ,pour une nouvelle partie, il genere une celule de sudoku aleatoire puis le commancement du jeu */

int StartGame(SDL_Surface* ecran,int** m, int** v,int temps,int load,player players){

    SDL_Surface *MapSudoku = NULL, *BoutonRejouer = NULL , *BoutonAccueil = NULL,*BoutonSave = NULL ,*BoutonRejouer_souris = NULL , *BoutonAccueil_souris = NULL,*BoutonSave_souris = NULL, *Forme_souris = NULL , *Name ;
    SDL_Surface *Forme[4] = {NULL};
    SDL_Rect PositionMapSudoku , PositionForme[4][4] , PositionRejouer , PositionAccueil ,PositionSave , PositionName ;
    SDL_Event event ;
    char user[20] = "";
    player player1;


    for (int i=0 ; i < 4 ; i++){
        for (int j=0 ; j < 4 ; j++){
            PositionForme[i][j].x = (i<2) ? (250+125*i) : (525 + (i-2)*125) ;
            PositionForme[i][j].y = (j<2) ? (50+125*j) : (325 + (j-2)*125) ;
        }
    }



    FMOD_SYSTEM *system;
    FMOD_SOUND *click,*miss,*save;


    /* Création et initialisation d'un objet système */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* Chargement du son */
    FMOD_System_CreateSound(system, "sound/click.wav", FMOD_CREATESAMPLE, 0, &click);
    FMOD_System_CreateSound(system, "sound/Miss.wav", FMOD_CREATESAMPLE, 0, &miss);
    FMOD_System_CreateSound(system, "sound/save.wav", FMOD_CREATESAMPLE, 0, &save);

    PositionMapSudoku.x = 0;
    PositionMapSudoku.y = 0;

    PositionAccueil.x = 25;
    PositionAccueil.y = 525 ;

    PositionSave.x = 25;
    PositionSave.y = 425 ;

    PositionRejouer.x = 25 ;
    PositionRejouer.y = 325 ;

    int continuer = 1,notsaved = 1;




    MapSudoku = SDL_LoadBMP("image/map3.bmp");
    BoutonAccueil = IMG_Load("image/acc.png");
    BoutonSave = IMG_Load("image/save.png");
    BoutonRejouer = IMG_Load("image/rejouer.png") ;
    BoutonAccueil_souris = IMG_Load("image/acc_souris.png");
    BoutonSave_souris = IMG_Load("image/save_souris.png");
    BoutonRejouer_souris = IMG_Load("image/rejouer_souris.png") ;
    Forme_souris =  IMG_Load("image/forme_souris.png") ;

    Forme[0] = IMG_Load("image/forme1.png");
    Forme[1] = IMG_Load("image/forme2.png");
    Forme[2] = IMG_Load("image/forme3.png");
    Forme[3] = IMG_Load("image/forme4.png");

    SDL_SetColorKey(Forme[0], SDL_SRCCOLORKEY, SDL_MapRGB (Forme[0]->format, 255, 0, 0));

    for(int i = 1 ; i<5 ; i++){
        SDL_SetColorKey(Forme[i], SDL_SRCCOLORKEY, SDL_MapRGB(Forme[i]->format, 0, 0, 255));
    }

    temps = SDL_GetTicks();

    if (load){
        continuer = Username(ecran,user) ;
        strcpy(player1.name,user);
        rejouer :
        do {
            NewGameFct(m,v);
        }while(sudoku_est_valide(m)==0) ;
        mode_facile(m,v) ;
    }
    else {
        strcpy(player1.name,players.name);
        temps -= players.time ;
        for (int k = 0 ; k < 4 ; k ++){
            for (int l = 0 ; l < 4 ; l ++){
                m[k][l] = players.matrice [k][l];
                v[k][l] = players.inchangable[k][l];
            }
        }
    }


    PositionName.x = 25 ;
    PositionName.y = 200 ;




    print:

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(MapSudoku, NULL, ecran, &PositionMapSudoku);
    SDL_BlitSurface(BoutonAccueil, NULL, ecran, &PositionAccueil);
    SDL_BlitSurface(BoutonSave, NULL, ecran, &PositionSave);
    SDL_BlitSurface(BoutonRejouer, NULL, ecran, &PositionRejouer);

    for (int i=0 ; i < 4 ; i++){
        for (int j=0 ; j < 4 ; j++){
            if (m[i][j]){
                SDL_BlitSurface(Forme[m[i][j]-1], NULL, ecran, &PositionForme[i][j]);
            }
        }
    }



    SDL_Flip(ecran);

    while (continuer && sudoku_est_valide(m)==0 )
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
                        continuer = 0;
                        break;
                }
            case SDL_MOUSEBUTTONUP:

                if (event.button.button == SDL_BUTTON_LEFT){/* On arrête le programme si on a fait un clic droit */
                    if (IsMouseInBoutton2(PositionAccueil,event.button.x,event.button.y)){
                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                            continuer = 0 ;
                            break ;
                    }
                    else if (IsMouseInBoutton2(PositionRejouer,event.button.x,event.button.y)){
                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, click, 0, NULL);
                            goto rejouer;
                            break ;
                    }
                    else if (IsMouseInBoutton2(PositionSave,event.button.x,event.button.y) && notsaved){
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, save, 0, NULL);
                            for (int i=0 ; i < 4 ; i++){
                                for (int j=0 ; j < 4 ; j++){
                                    player1.inchangable[i][j] = v[i][j];
                                    player1.matrice[i][j]=m[i][j];
                                }
                            }
                            sauvgarder(player1,temps);
                            notsaved = 0 ;
                            break ;
                    }
                    else {
                        for (int i = 0 ; i < 4 ; i ++){
                            for (int j = 0 ; j < 4 ; j ++){
                                if (IsMouseInForme(PositionForme[i][j],event.button.x,event.button.y)){
                                        if (v[i][j]==0){
                                            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, miss, 0, NULL);
                                            if (m[i][j]==4) m[i][j] = 0 ;
                                            else m[i][j]++ ;
                                            goto print ;
                                        }
                                    break ;
                                }
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION :
                if (IsMouseInBoutton2(PositionAccueil,event.button.x,event.button.y)){
                    SDL_BlitSurface(BoutonAccueil_souris, NULL, ecran, &PositionAccueil);
                    SDL_Flip(ecran);
                    }
                else if (IsMouseInBoutton2(PositionRejouer,event.button.x,event.button.y)){
                    SDL_BlitSurface(BoutonRejouer_souris, NULL, ecran, &PositionRejouer);
                    SDL_Flip(ecran);
                    }
                else if (IsMouseInBoutton2(PositionSave,event.button.x,event.button.y) && notsaved){
                    SDL_BlitSurface(BoutonSave_souris, NULL, ecran, &PositionSave);
                    SDL_Flip(ecran);
                }
                else {
                    int a = 1 ;
                    for (int i = 0 ; i < 4 ; i ++){
                            for (int j = 0 ; j < 4 ; j ++){
                                if (IsMouseInForme(PositionForme[i][j],event.button.x,event.button.y)){
                                    if (v[i][j]==0){
                                        SDL_BlitSurface(Forme_souris, NULL, ecran, &PositionForme[i][j]);
                                        SDL_Flip(ecran);
                                        a = 0 ;
                                        break ;

                                    }
                                }
                            }
                        }
                    if (a)
                    goto print ;
                }
            }
        }


    if (continuer){
        FctScore(ecran,temps,player1.name);
    }

    SDL_FreeSurface(MapSudoku);
    SDL_FreeSurface(BoutonAccueil);
    SDL_FreeSurface(BoutonRejouer);
    SDL_FreeSurface(BoutonSave);
    SDL_FreeSurface(BoutonRejouer_souris);
    SDL_FreeSurface(BoutonAccueil_souris);
    SDL_FreeSurface(BoutonSave_souris);
    SDL_FreeSurface(Forme_souris);
    for(int i = 0 ; i < 4 ; i++){
        SDL_FreeSurface(Forme[i]);
    }
    FMOD_Sound_Release(click);
    FMOD_Sound_Release(miss);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    return 0 ;
}

/* la fonction qui assure la generation d'une celule du sudoku remlie */

void NewGameFct(int** m,int** v) {

        initialiser(m,v);

        remplir_sudoku(m);

}

/* la fonction qui detecte si le sudoku est valide ou pas */

int sudoku_est_valide(int **m){
	int s = 0 , i , j ;
	for (i=0;i<4;i++){
		s = 0 ;
		for (j=0;j<4;j++){
			s+=m[i][j];
		}
		if (s!=10) return (0);
	}
	for (i=0;i<4;i++){
		s = 0 ;
		for (j=0;j<4;j++){
			s+=m[i][j];
		}
		if (s!=10) return (0) ;
	}
	for (i=0;i<4;i+=2){
		s = 0 ;
		for (j=0;j<4;j+=2) {
			s+=m[i][j];
			s+=m[i][j+1];
			s+=m[i+1][j];
			s+=m[i+1][j+1];
			if (s!=10) return (0) ;
			s = 0 ;
		}

	}
	return (1) ;
}

/* c'est la fonction qui suprime un nempbre precise de case de la celule generer du sudoku qui est complete (assurer l'existance de la
  solution */

void mode_facile(int** m,int** v){
	int x,y;
	for (int i=0;i<NOMBRE_ELEMENT_A_SUPPRIMER;i++){
		do {
			x=rand()%4;
			y=rand()%4;
		}while (v[x][y]==0);
		v[x][y]=0 ;
		m[x][y]=0 ;
	}
}

/* c'est la fonction qui detecte si la souris est sur un bouton ou pas ! */

int IsMouseInBoutton2(SDL_Rect bouton , int x , int y){
    if (   y >= bouton.y
        && y <= bouton.y + BOUTON2_HAUTEUR
        && x >= bouton.x
        && x <= bouton.x + BOUTON2_LARGEUR)
        return 1;
    return 0;
}

/* c'est la fonction qui detecte si la souris est sur une case du sudoku ou pas ! */

int IsMouseInForme(SDL_Rect bouton , int x , int y){
    if (   y >= bouton.y
        && y <= bouton.y + FORME_LARGEUR
        && x >= bouton.x
        && x <= bouton.x + FORME_LARGEUR)
        return 1;
    return 0;
}

/* renitialiser le sudoku pas des zeros */

void initialiser(int** m,int** v){
	for (int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			m[i][j]=0;
			v[i][j]=1;
		}
	}
}

/* La fonction que detecte si un chiffre est redoubler su une ligne/colonne ou pas */

int existe(int** m,int i,int j,int valeur){
	for(int k=0;k<4;k++){
		if (m[i][k]==valeur || m[k][j]==valeur) {
			return 0 ;
		}
	}
	return 1 ;
}

/* c'est le coeur du jeu , c'est la fonction qui remplit tous le sudoku pas des valeurs valide ! */

void remplir_sudoku(int** m){
	int i,j,r;
	int chiffre[4]={0,0,0,0} ;

	for (i=0;i<2;i++){
		for(j=0;j<2;j++){
			do{
				r=rand()%4;
			} while (chiffre[r]==1);
			m[i][j]=r+1;
			chiffre[r]=1;
		}
	}

	for (i=0;i<4;i++){
		chiffre[i]=0;
	}

	for (i=0;i<2;i++){
		for(j=0;j<2;j++){
			do{
				r=rand()%4;
			} while (chiffre[r]==1);
			m[i+2][j+2]=r+1;
			chiffre[r]=1;
		}
	}
	for (i=0;i<2;i++){
		for (j=2;j<4;j++){
			for (int valeur=1;valeur<5;valeur++){
				if (existe(m,i,j,valeur)){
					m[i][j]=valeur ;
					break ;
				}
			}
		}
	}
	for (i=2;i<4;i++){
		for (j=0;j<2;j++){
			for (int valeur=1;valeur<5;valeur++){
				if (existe(m,i,j,valeur)){
					m[i][j]=valeur ;
					break ;
				}
			}
		}
	}

}
