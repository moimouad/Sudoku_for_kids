#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>


typedef struct {
    char name[20];
    int score ;
}playerscore ;

void TrasformerTempsEnChar(int Now,char* temps);
void SauvgarderScore(int now,char* name);

#endif // SCORE_H_INCLUDED
