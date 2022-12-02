#ifndef BOUTIQUE_H
#define BOUTIQUE_H
#include "Deck.h"
#include "Joueur.h"
#include "Terrain.h"

class Boutique
{
private:
    Joueur m_joueur;        //joueur connecté
    Deck m_collection;      //collection existante
    Deck m_joueurDeck;      //collection du joueur
    int m_prix;             //prix d'une carte
    Terrain m_plato;
public:
    Boutique(Joueur j, Terrain t);
    ~Boutique();
    void achatCarte();      //methode pour que le joueurs achète une carte;
};

#endif // BOUTIQUE_H_INCLUDED
