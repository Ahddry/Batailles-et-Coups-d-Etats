#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED
#include "Joueur.h"
#include "Deck.h"
class Switch
{
private:
    Joueur m_j1;        //Joueur qui veux changer ses carte
    Deck m_colecJ;      //Collection du joueur
    Deck m_deckJ;       //deck du joueur
    Terrain m_plato;
public:
    Switch(Joueur j1, Terrain t);
    ~Switch();
    void ajoutCarteDeck();  //M�thode pour ajouter une carte de la collection dans le deck
    void removeCarteDeck(); //M�thode pour enlever une carte du dec
    bool testDoubleCarte(Carte* carte);//M�thode pour verifier si la carte n'est pas d�j� dans le deck
};


#endif // SWITCH_H_INCLUDED
