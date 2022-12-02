#include "Boutique.h"
#include <iostream>
#include "Deck.h"
#include "Joueur.h"
#include <string>
#include <vector>
Boutique::Boutique(Joueur j1, Terrain t)///Constucteur de la boutique prenant en entrée le joueur qui souhaite aller dans la boutique
    : m_plato(t)
{
    m_prix=2;//initialisation du prix
    m_joueur = j1;
    Deck collection("Collection.txt");
    m_collection = collection;//récupération de la collection universelle existante
    m_joueurDeck = m_joueur.getCollection();//récupération de la collection du joueur
    int choix=0;
    bool fin = false;
    while(!fin)//tant que le choix n'est pas de quitter
    {
        m_plato.effacer();
        m_joueur.actualiserDeck();
        std::vector<std::string> propos;
        //std::cout << "Vous avez " << m_joueur.getMoney() << " coins !" << std::endl;
        propos.push_back("Voir toutes les cartes disponibles");
        propos.push_back("Voir ma collection");
        propos.push_back("Acheter une carte");
        propos.push_back("Retourner au menu principal");
        choix = m_plato.menu("Boutique", propos, 4);
        switch(choix)
        {
        case 1:///si choix est voir cartes existante
            {
                m_plato.affDeck(m_collection, 1);    //appel méthode d'affichage
                break;
            }
        case 2:///si choix est voir la collection du joueur
            {
                m_plato.affDeck(m_joueurDeck, 1);    //méthode pour afficher toutes les cartes de la collection du joueur
                break;
            }
        case 3:///si choix est d'acheter une carte
            {
                achatCarte();
                break;
            }
        case 4:///si choix est de quitter
                fin = true;
                break;
        default:
            {
                m_plato.erreur("Entree incorecte");
            }
        }
    }
}

Boutique::~Boutique()///Destructeur boutique
{

}
void Boutique::achatCarte()///Achat d'une carte
{
    Carte* c;
    m_plato.effacer();
    m_plato.argent(m_joueur.getMoney());
    m_plato.emphase("Choisissez une carte", "Retenez bien son numero");
    rest(1500);
    m_plato.effacer();
    m_plato.affDeck(m_collection, 1);
    m_plato.effacer();
    m_plato.argent(m_joueur.getMoney());
    int choix = atoi(m_plato.saisie("Choisissez une carte", "Quel est votre choix ?").c_str());
    std::vector<Carte*> vec = m_collection.getDeck();

    int maxcarte = vec.size()+1;
    if(choix<maxcarte)
    {
        c = vec[choix-1];
        m_plato.affCarte(SCREEN_W/2-150, SCREEN_H/2+50, c);
        m_plato.argent(m_joueur.getMoney());
        m_plato.afficher();
        m_plato.emphase("Vous avez choisi", "La carte " + c->getNom());
        rest(2500);
        if(m_joueur.getMoney()>=m_prix)//si le joueur a assez d'argent
        {
            m_joueurDeck.remettre(c);//ajout de la carte achetée a la collection du joueur
            m_joueurDeck.ecrireDeck(m_joueur.getDossier()+"Collection.txt");//sauvegarde du fichier collection du joueur
            m_joueur.removeMoney(m_prix);//on enlève le prix de la carte au joueur
        }
        else
        {
            m_plato.erreur("Vous n'avez pas assez d'argent, il vous manque " + std::to_string(m_prix-m_joueur.getMoney())+" coin(s)");
        }
    }
    else
    {
        m_plato.erreur("Vous n'avez pas choisi une vraie carte.");
    }

}
