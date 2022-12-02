#include "Cartes.h"
#include <string>
#include <iostream>
Carte::Carte(){}
Carte::Carte(std::string nom = "", std::string nature = "Indefini")  //Constructeur créant une carte en lui donnant un nom et une nature.
{
    m_nom = nom;
    m_nature = nature;
}
 Carte::~Carte(){}

std::string Carte::getNom() const //Getter pour le nom
{
    return m_nom;
}

int Carte::getPV() const        //Getter pour les PVs
{
    return 0;
}
void Carte::setMultiplicateur(int multi){} //Setter pour le multiplicateur de dégâts, utile seulement pour les dirigeants en cours de partie
std::string Carte::getNature()              //Getter pour la nature
{
    return m_nature;
}
Pouvoir Carte::getPouvoir()   //Getter pour le Pouvoir, nécessaire pour les classes filles
{
    Pouvoir p;
    return p;
}

int Carte::attaquer(int numAttaq)       //Méthode utile pour les dirigeants en cours de partie
{
    return 0;
}
int Carte::subir(int nbDegats)      //Méthode utile pour les dirigeants en cours de partie
{
    return 0;
}

void Carte::affichage() const {std::cout<<"TEST"<<std::endl;}//Affichage de la carte

std::string Carte::ecriture()           //Ecriture de la carte dans un fichier
{
    std::string ecriture = "INDEFINI\n";
    ecriture += m_nom + "\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    return ecriture;
}
std::vector<std::string> Carte::graphisme() const //Envoie de toutes les informations pour affichage graphique avec Allegro
{
    std::vector<std::string> infos;
    return infos;
}
