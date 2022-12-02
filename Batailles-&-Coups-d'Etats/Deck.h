#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED
#include "Cartes.h"
#include "Energie.h"
#include "Dirigeant.h"
#include "Pouvoir.h"
#include "Attaque.h"
#include "Speciale.h"
#include <string>
#include <vector>
///Classe génrant des paquets de Cartes
class Deck
{
private:
    std::vector<Carte*> m_deck;         //Paquet de carte
public:
    Deck();
    Deck(std::vector<Carte*> deck);
    Deck(const Deck& deck);
    Deck(const std::string emplacement);
    ~Deck();

    std::vector<Carte*> getDeck() const;    //Getter pour le paquet sous forme de vector
    void melanger();                        //Méthode pour mélanger un vector obtenue sur https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    Carte* piocher();                       //Getter pour la carte au-dessus du paquet, en l'enlevant de celui-ci
    void remettre(Carte* carte);            //Insertion d'un carte en-dessous du paquet
    void retirer(std::string nomCarte);     //Suppression du paquet d'une carte particulière en donnant son nom
    void ecrireDeck(const std::string fichier); //Ecriture du paquet dans un fichier
};

#endif // DECK_H_INCLUDED
