#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED
#include "Terrain.h"
#include <string>
#include <vector>

class Scores
{
private:
    std::string m_fichier;              //Fichier de score des joueurs
    std::vector<std::string> m_joueurs; //tableau des joueurs ayant un compte
    std::vector<int> m_victoires;       //tableau des victoires
    Terrain m_terrain;                  //affichage graphique
public:
    Scores(Terrain t);                  //Creation du tableau des scores
    ~Scores();
    void save();                        //Sauvegarde du fichier des victoires
    void ajoutVictoire(std::string joueur);//Ajout d'une victoire pour un joueur donné
    void ajoutJoueur(std::string joueur);//Ajout d'un nouveau joueur au fichier
    void tri();                         //Tri des tableaux par ordre du joueur ayant le plus de victoires
    void affichage();                   //Affichage des 7 meilleurs joueurs du jeu
};

#endif // SCORES_H_INCLUDED
