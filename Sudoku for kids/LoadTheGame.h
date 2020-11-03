#ifndef LOADTHEGAME_H_INCLUDED
#define LOADTHEGAME_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>

#define POSITION_X 5
#define POSITION_Y 105
#define BOUTON_LARGEUR 200
#define BOUTON_HAUTEUR 50
#define LOAD_HAUTEUR 40
#define LOAD_LARGEUR 790

typedef struct {
    char name[20];
    int matrice[4][4],inchangable[4][4];
    int time ;
}player;

int  IsMouseInLoad(SDL_Rect bouton, int x , int y) ;
int StartGame(SDL_Surface* ecran,int** m, int** v,int temps,int load, player players) ;





#endif // LOADTHEGAME_H_INCLUDED
