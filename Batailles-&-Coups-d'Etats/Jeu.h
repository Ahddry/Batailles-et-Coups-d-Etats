#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include "Joueur.h"
#include "Cartes.h"
#include "Dirigeant.h"
#include "Attaque.h"
#include "Pouvoir.h"
#include "Energie.h"
#include "Speciale.h"
#include "Deck.h"
#include <string>
#include <vector>
#include "Terrain.h"
///Classe s'occupant du d�roulement d'une partie
class Jeu
{
private:
    Joueur m_j1;                //Joueur 1
    Joueur m_j2;                //Joueur 2
    Deck m_deck1;               //Deck du joueur 1
    Deck m_deck2;               //Deck du joueur 2
    std::vector<int> m_pouvoir1;//Points de pouvoir du joueur 1
    std::vector<int> m_pouvoir2;//Points de pouvoir du joueur 2
    std::vector<Carte*> m_cimentiere1;//Cimeti�re du joueur 1
    std::vector<Carte*> m_cimentiere2;//Cimeti�re du joueur 2
    Carte* m_enjeu1;            //Carte tir�e comme enjeu pour le joueur 1
    Carte* m_enjeu2;            //Carte tir�e comme enjeu pour le joueur 2
    Carte* m_dirigeant1;        //Dirigeant actif pour le joueur 1
    Carte* m_dirigeant2;        //Dirigeant actif pour le joueur 2
    Joueur m_vainqueur;         //Joueur vainqueur de la partie
    int m_pvJ1;                 //PV du joueur 1
    int m_pvJ2;                 //PV du joueur 2
    int m_famine;               //Variable de la carte sp�ciale persistante famine
    bool m_francisque;          //Varaible de la carte francisque
    Terrain m_terrain;          //Plateau de jeu

unsigned m_plateau;
public:
    Jeu(Joueur j1, Joueur j2, Terrain t);
    ~Jeu();
    void effetSpeciaux(int nbJoueur, std::string nomCarte);         //M�thode pour l'activation des cartes sp�ciales
    void enjeu(int nbJoueur);                                       //Attribution de l'enjeu au vainqueur
    void tour(int nbJoueur);                                        //Deroulement d'un tour pour le joueur plac�e en param�tre
    bool coutAttaque(int nbAttaque, int nbJoueur, int typeAttaque); //Calcul de la posibilit� et des co�t d'une attaque
    bool attaquer(int nbAttaque, int nbJoueur);                     //R�alisation d'une attaque
    void deroulementJeu();                                          //D�roulement d'une partie

};

#endif // JEU_H_INCLUDED
