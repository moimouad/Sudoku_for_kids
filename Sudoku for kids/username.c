#include "username.h"

/* c'est la fonction qui affiche la page du saisie du nom du jouer */

int Username(SDL_Surface* ecran,char* user){
    SDL_Surface *PassWordPage = NULL ,*texte = NULL ;
    SDL_Rect PositionPasseWordPage ,position;
    SDL_Event event ;
    int continuer = 1;


    TTF_Init();

    PositionPasseWordPage.x = 0 ;
    PositionPasseWordPage.y = 0 ;
    position.x = 350;
    position.y = 270;

    PassWordPage = SDL_LoadBMP("image/username.bmp");

    TTF_Font *police = NULL;
    SDL_Color couleurB = {255, 255, 255};
    police = TTF_OpenFont("font/font2.ttf", 50);
    while (continuer && strlen(user)< 16 )
    {

        texte = TTF_RenderText_Blended(police, user , couleurB);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(PassWordPage, NULL, ecran, &PositionPasseWordPage);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_Flip(ecran);


        SDL_WaitEvent(&event); /* Récupération de l'événement dans event */
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                TTF_CloseFont(police);
                TTF_Quit();
                SDL_FreeSurface(texte);
                SDL_FreeSurface(PassWordPage);
                return 0 ;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_RETURN:
                        TTF_CloseFont(police);
                        TTF_Quit();
                        SDL_FreeSurface(texte);
                        SDL_FreeSurface(PassWordPage);
                        return 1 ;
                        break;
                    case SDLK_BACKSPACE:
                        if (strlen(user)){
                            user[strlen(user)-1] = '\0' ;
                        }
                        break ;
                    case SDLK_q:
                        strcat(user,"a");
                        break ;
                    case SDLK_b:
                        strcat(user,"b");
                        break ;
                    case SDLK_c:
                        strcat(user,"c");
                        break ;
                    case SDLK_d:
                        strcat(user,"d");
                        break ;
                    case SDLK_e:
                        strcat(user,"e");
                        break ;
                    case SDLK_f:
                        strcat(user,"f");
                        break ;
                    case SDLK_g:
                        strcat(user,"g");
                        break ;
                    case SDLK_h:
                        strcat(user,"h");
                        break ;
                    case SDLK_i:
                        strcat(user,"i");
                        break ;
                    case SDLK_j:
                        strcat(user,"j");
                        break ;
                    case SDLK_k:
                        strcat(user,"k");
                        break ;
                    case SDLK_l:
                        strcat(user,"l");
                        break ;
                    case SDLK_SEMICOLON:
                        strcat(user,"m");
                        break ;
                    case SDLK_n:
                        strcat(user,"n");
                        break ;
                    case SDLK_o:
                        strcat(user,"o");
                        break ;
                    case SDLK_p:
                        strcat(user,"p");
                        break ;
                    case SDLK_a:
                        strcat(user,"q");
                        break ;
                    case SDLK_r:
                        strcat(user,"r");
                        break ;
                    case SDLK_s:
                        strcat(user,"s");
                        break ;
                    case SDLK_t:
                        strcat(user,"t");
                        break ;
                    case SDLK_u:
                        strcat(user,"u");
                        break ;
                    case SDLK_v:
                        strcat(user,"v");
                        break ;
                    case SDLK_z:
                        strcat(user,"w");
                        break ;
                    case SDLK_x:
                        strcat(user,"x");
                        break ;
                    case SDLK_y:
                        strcat(user,"y");
                        break ;
                    case SDLK_w:
                        strcat(user,"z");
                        break ;
                    case SDLK_SPACE:
                        strcat(user," ");
                        break ;

                }
            break;

        }
    }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_FreeSurface(PassWordPage);
    return 1 ;
}
