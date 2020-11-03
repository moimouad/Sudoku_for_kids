#ifndef SAUVGARDE_H_INCLUDED
#define SAUVGARDE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

typedef struct {
    char name[20];
    int matrice[4][4],inchangable[4][4];
    int time ;
}player;

#endif // SAUVGARDE_H_INCLUDED
