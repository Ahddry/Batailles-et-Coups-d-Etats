#include <iostream>
#include "Joueur.h"
#include "Deck.h"
#include "Switch.h"

Switch::Switch(Joueur j1, Terrain t)///Constructeur de la classe prenant en entrée le Joueur qui veux modifier son deck
    : m_plato(t)
{
    m_j1=j1;
    m_colecJ=m_j1.getCollection();//récupération de la collection du joueur
    m_deckJ=m_j1.getDeck();//récupération du deck du joueur
    int choix=0;
    while(choix!=5)
    {
        m_plato.effacer();
        m_j1.actualiserDeck();
        std::vector<std::string> propos;//Chargement des propositions du menu
        propos.push_back("Voir ma collection");
        propos.push_back("Voir mon deck");
        propos.push_back("Ajouter une carte a mon deck");
        propos.push_back("Enlever une carte a mon deck");
        propos.push_back("Retourner au menu principal");
        choix = m_plato.menu("Conception de deck", propos, 5);
        switch(choix)
        {
        case 1://si choix est voir collection du joueur
            {
                m_plato.affDeck(m_colecJ, 1);
                break;
            }
        case 2://si choix est voir deck du joueur
            {
                m_plato.affDeck(m_deckJ, 1);
                break;
            }
        case 3://si choix est ajouter une carte au deck
            {
                if(m_deckJ.getDeck().size()<=25)
                    ajoutCarteDeck();
                else
                    m_plato.erreur("Erreur tu a deja un nombre maximun de carte dans ton deck");
                break;
            }
        case 4://si choix est enlever une carte du deck
            {
                removeCarteDeck();
                break;
            }
        case 5://si choix est quitter
            {
                break;
            }
        default://si entrée incorrecte
            {
                m_plato.erreur("Choix impossible");
            }
        }
    }
}
Switch::~Switch()
{

}

void Switch::ajoutCarteDeck()///Méthode pour ajouter une carte au deck du joueur
{
    if(m_deckJ.getDeck().size()<=25)
    {
        Carte* c;
        m_plato.effacer();
        m_plato.emphase("Choisissez une carte a jouter", "Retenez bien son numero");
        rest(1500);
        m_plato.effacer();
        m_plato.affDeck(m_colecJ, 1);//Affichage du deck
        m_plato.effacer();
        int choix = atoi(m_plato.saisie("Choisissez une cartea ajouter", "Quel est votre choix ?").c_str());
        std::vector<Carte*> vec = m_colecJ.getDeck();
        int maxcarte = vec.size()+1;
        if(choix<maxcarte)//si le choix n'est pas de quitter
        {
            c = vec[choix-1];
            m_plato.affCarte(SCREEN_W/2-150, SCREEN_H/2+50, c);
            m_plato.afficher();
            m_plato.emphase("Vous avez choisi", "La carte " + c->getNom());
            rest(2500);
            if(testDoubleCarte(c)==true)//si la carte n'est pas présente dans le deck
            {
                if(m_deckJ.getDeck().size()>=25)//si le deck n'est pas deja plein
                {
                    m_plato.erreur("Votre deck contient deja 25 cartes, le nombre maximum !");
                }
                else
                {
                    m_plato.effacer();
                    m_plato.emphase("La carte " + c->getNom(), "A ete ajoute a votre deck !");
                    m_deckJ.remettre(c);//ajout de la carte au deck
                    m_deckJ.ecrireDeck(m_j1.getDossier()+"deck.txt");//sauvegarde du deck du joueur dans son fichier
                    rest(1300);
                }
            }
            else//si la carte est déja dans le deck
            {
                m_plato.erreur("Cette carte est deja dans votre deck !");
            }
        }
        else
        {
            m_plato.effacer();
            m_plato.erreur("Il faut choisir une vraie carte !");
        }
    }
    else
    {
       m_plato.erreur("Vous avez deja le nombre maximum de carte dans votre deck");
    }
}
void Switch::removeCarteDeck()///Méthode pour enlever une carte au deck du joueur
{
    Carte* c;
    m_plato.effacer();
    m_plato.emphase("Choisissez une carte a retirer", "Retenez bien son numero");
    rest(1500);
    m_plato.effacer();
    m_plato.affDeck(m_deckJ, 1);//Affichage du deck
    m_plato.effacer();
    int choix = atoi(m_plato.saisie("Choisissez une carte a retirer", "Quel est votre choix ?").c_str());
    std::vector<Carte*> vec = m_deckJ.getDeck();

    int maxcarte = vec.size()+1;
    if(choix<maxcarte)
    {
        c = vec[choix-1];
        m_plato.affCarte(SCREEN_W/2-150, SCREEN_H/2+50, c);//Affichage de la carte choisie
        m_plato.afficher();
        m_plato.emphase("Vous avez retire", "La carte " + c->getNom());
        rest(2500);

        m_deckJ.retirer(c->getNom());//on enleve la carte choisie du deck
        m_deckJ.ecrireDeck(m_j1.getDossier()+"deck.txt");//on sauvegarde le deck dans son fichier
    }
    else
    {
        m_plato.erreur("Vous n'avez pas choisi une vraie carte.");
    }
}
bool Switch::testDoubleCarte(Carte* carte)///Méthode pour verifier si la carte n'est pas déja dans le deck qui prend en entrée la carte choisie et qui retourne un booléen
{
    std::vector<Carte*> deck = m_deckJ.getDeck();//on récupére le deck du joueur
    std::vector<Carte*> vec = m_colecJ.getDeck();//on récupére la collection du joueur
    std::string carteName = carte->getNom();//on récupére le nom de la carte entrée
    int nbcol=0;
    int nbdeck=0;
    for(const auto& elem:vec)
    {
        if(elem->getNom()==carte->getNom())//si la carte a le même nom que la carte choisi
            nbcol++;
    }

    for(const auto& test:deck)
    {
        if(test->getNom()==carte->getNom())//si la carte a le même nom que la carte choisi
        {
            nbdeck++;
        }
    }
    if(nbcol>nbdeck)
    {//si la carte n'est pas dans le deck
        return true;
    }
    else//si la carte est dans le deck
    {
        return false;
    }
}
