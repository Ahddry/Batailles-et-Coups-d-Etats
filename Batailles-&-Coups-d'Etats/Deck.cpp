#include "Deck.h"
#include "Cartes.h"
#include "Pouvoir.h"
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <iostream>
#include <fstream>
#include <string>

Deck::Deck(){}                      ///Constructeur pour un paquet de carte vide
Deck::Deck(std::vector<Carte*> deck)///Constructeur en donnant un vector contenant des cartes
{
    m_deck = deck;
}
Deck::Deck(const Deck& deck)        ///Constructeur par copie d'un autre paquet de cartes
{
    m_deck = deck.getDeck();
}

Deck::Deck(const std::string emplacement)   ///Constructeur d'un paquet de carte par lecture en fournissant l'emplacement du fichier où il est enregistré
{
    std::vector<std::string> vect;
    std::ifstream fichier(emplacement);
    if(fichier)                         //Vérification de l'existance du fichier
    {
        std::string ligne;
        while(getline(fichier, ligne))
        {
            vect.push_back(ligne);      //Lecture de l'intégralité du fichier et stockage de celui-ci dans un vector
        }
    }
    //else {std::cout<<"erreur";}
    std::vector<Carte*> deck;
    for(unsigned int i = 0; i<vect.size(); i+=11)
    {
        if(vect[i]=="ENERGIE")      //Détection et construction d'une carte énergie
        {
            std::string nom = vect[i+1];
            std::string p = vect[i+2];
            Pouvoir pouv(p);
            std::string legende = vect[i+3];
            deck.push_back(new Energie(nom, p, legende));   //Ajout de la carte énergie au paquet
        }
        if(vect[i]=="DIRIGEANT")    //Détection et construction d'une carte Dirigeant
        {
            std::string temp;
            std::string nom = vect[i+1];
            int pv = atoi(vect[i+2].c_str());
            std::vector<Pouvoir> pouvAttaque1;
            std::string nomAttaque = vect[i+3];
            std::vector<Pouvoir> type1;
            temp = vect[i+4];
            Pouvoir p1(temp);
            type1.push_back(p1);
            Attaque a1(nomAttaque, type1, 1);   //Construction d'une attaque
            nomAttaque =vect[i+5];
            std::vector<Pouvoir> type2;
            temp = vect[i+6];
            Pouvoir p2(temp);
            type2.push_back(p2);
            temp = vect[i+7];
            Pouvoir p3(temp);
            type2.push_back(p3);
            temp = vect[i+8];
            Pouvoir p4(temp);
            type2.push_back(p4);
            Attaque a2(nomAttaque, type2, 3);   //Construction d'une attaque
            temp = vect[i+9];
            Pouvoir p5(temp);
            deck.push_back(new Dirigeant(nom, pv, a1, a2, p5)); //Ajout de la carte Dirigeant créée au paquet
        }
        if(vect[i]=="SPECIALE")         //Détection et construction d'une carte Spéciale
        {
            std::string nom = vect[i+1];
            std::string effet = vect[i+2];
            std::string persistance = vect[i+3];
            deck.push_back(new Speciale(nom, effet, persistance));  //Ajout de la carte Spéciale créée au paquet
        }
    }
    m_deck = deck;
}

Deck::~Deck(){}

std::vector<Carte*> Deck::getDeck() const   //Getter pour le paquet sous forme de vector
{
    return m_deck;
}

///https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
void Deck::melanger() //Méthode pour mélanger un vector obtenue sur stackoverflow
{                     //Utilisée ici pour mélanger notre paquet de carte
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(m_deck.begin(), m_deck.end(), std::default_random_engine(seed));
}

Carte* Deck::piocher()//Getter pour la carte au-dessus du paquet, en l'enlevant de celui-ci
{
    if(m_deck.empty())
    {
        //std::cout<<"LE DECK EST VIDE !!!"<<std::endl;
        return 0;
    }
    else
    {
        Carte* pioche = m_deck.back();
        m_deck.pop_back();
        return pioche;
    }
}

void Deck::remettre(Carte* carte)//Insertion d'un carte en-dessous du paquet
{
    m_deck.insert(m_deck.begin(), carte);
}

void Deck::retirer(std::string nomCarte)    //Suppression du paquet d'un carte particulière en donnant son nom
{
    bool supression = false;
    std::vector<Carte*> buffer;
    while(!m_deck.empty())
    {
        buffer.push_back(m_deck.back());
        m_deck.pop_back();
    }
    while(!buffer.empty())
    {
        if(!supression)
        {
            if(buffer.back()->getNom()==nomCarte)
            {
                nomCarte = ".......£....!.!!!.";    //Sécurité pour ne retirer la carte qu'une seule fois
                buffer.pop_back();
                supression = true;
            }
            else
            {
                m_deck.push_back(buffer.back());
                buffer.pop_back();
            }
        }
        else
        {
            m_deck.push_back(buffer.back());
            buffer.pop_back();
        }
    }

}
void Deck::ecrireDeck(const std::string fichier )//Ecriture du paquet dans un fichier
{
    std::ofstream fichierDeck(fichier.c_str());

    if(fichierDeck)                 //Vérification de la possibilité d'ouverture du fichier
    {
        for(const auto& elem: m_deck)
        {
            fichierDeck << elem->ecriture();
            fichierDeck << std::endl;
        }
    }
    else
    {
        //std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}
