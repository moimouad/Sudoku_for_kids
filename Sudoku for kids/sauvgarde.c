#include "sauvgarde.h"

/*c'est la foction qui sauvgarde une partie dans le fichier du sauvgarde */

void sauvgarder(player player1,int temps){
    int Now = SDL_GetTicks();
    Now -= temps  ;
    player1.time = Now ;
    FILE* file ;
    file = fopen("sauvgarde.ensias","ab");
    fseek(file,0,0);//le curseur vers le debut du fichier
    fwrite(&player1,sizeof(player),1,file);
    fclose(file);
}
