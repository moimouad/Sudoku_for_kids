#ifndef NEWGAME_H_INCLUDED
#define NEWGAME_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>

#define NOMBRE_ELEMENT_A_SUPPRIMER 8
#define BOUTON2_LARGEUR 150
#define BOUTON2_HAUTEUR 50
#define FORME_LARGEUR 100

typedef struct {
    char name[20];
    int matrice[4][4],inchangable[4][4];
    int time ;
}player;

void NewGameFct(int** m,int** v);
int  sudoku_est_valide(int **m);
void mode_facile(int** m,int** v);
int  IsMouseInBoutton2(SDL_Rect bouton, int x , int y) ;
int  IsMouseInForme(SDL_Rect bouton, int x , int y) ;
void FctScore(SDL_Surface* ecran,int Temps,char* name);
void initialiser(int** m, int** v);
void remplir_sudoku(int** m);
int  existe(int** m,int i,int j,int valeur);
int Username(SDL_Surface* ecran,char* user);
void sauvgarder(player player1,int temps);
#endif // NEWGAME_H_INCLUDED
