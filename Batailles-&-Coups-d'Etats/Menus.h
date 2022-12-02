#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "Terrain.h"
#include "Joueur.h"
#include "Jeu.h"
#include "Attaque.h"
#include "Boutique.h"
#include "Switch.h"
class Menus
{
private:
    Terrain m_terrain;      //Affichage graphique
    Joueur m_joueur;        //Joueur connecté
public:
    Menus(Terrain t);
    ~Menus();
    bool principal();       //menu principal
    bool extras();          //menu des extensions
    bool creationCarte();   //menu de l'extension de création de cartes
    Attaque attaque(int numAttaque, Pouvoir type);//creation d'une attaque
};

#endif // MENUS_H_INCLUDED
