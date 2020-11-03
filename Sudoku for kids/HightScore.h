#ifndef HIGHTSCORE_H_INCLUDED
#define HIGHTSCORE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>

#define POSITION_X 50
#define POSITION_Y 105
#define BOUTON_LARGEUR 200
#define BOUTON_HAUTEUR 50


typedef struct {
    char name[20];
    int score ;
}playerscore ;

int  IsMouseInLoad(SDL_Rect bouton, int x , int y) ;
void TrasformerTempsEnChar(int Now,char* temps);
void Tri_score() ;

#endif // HIGHTSCORE_H_INCLUDED
