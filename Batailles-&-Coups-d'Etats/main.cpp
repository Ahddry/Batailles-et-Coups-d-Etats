#include "Terrain.h"
#include "Menus.h"
int main(int argc, char *argv[])
{
    Terrain t("");              //Initialisation de l'affichage graphique

    Menus menus(t);
    bool fin = false;
    while(!fin)
    {
        fin = menus.principal();//Ouverture du menu tant que l'utilisateur ne souhaite pas en sortir
    }

    return 0;
}
END_OF_MAIN();                  //Instruction Allegro de fin de programme
