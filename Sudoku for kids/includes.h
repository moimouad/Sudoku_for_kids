#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>

#define MAIN_LARGEUR 800
#define MAIN_HAUTEUR 600
#define BOUTON_LARGEUR 200
#define BOUTON_HAUTEUR 50
#define PASSWORD "mouad"

typedef struct {
    char name[20];
    int matrice[4][4],inchangable[4][4];
    int time ;
}player;

int  IsMouseInBoutton(SDL_Rect bouton, int x , int y) ;
int StartGame(SDL_Surface* ecran,int** m, int** v,int temps,int load,player players) ;
int LoadTheGame(SDL_Surface* ecran,int** m, int** v,int temps) ;
int Identification(SDL_Surface* ecran);
void HightScore(SDL_Surface* ecran);
void about_us(SDL_Surface* ecran) ;


#endif
