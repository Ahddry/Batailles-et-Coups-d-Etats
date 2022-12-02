#include "Speciale.h"
#include <iostream>

Speciale::Speciale(){}  ///Constructeur par d�faut des cartes sp�ciales

Speciale::Speciale(std::string nom, std::string effet, std::string persistance) ///Cr�ation d'une carte Sp�ciale en donnant son nom, le descriptif de son effet et sa dur�e d'effet
    : Carte(nom, "Speciale"), m_effet(effet), m_persistance(persistance)
{
}
Speciale::~Speciale(){}
std::string Speciale::getNom() const//Getter pour le nom
{
    return m_nom;
}

int Speciale::getPV() const//Getter pour les PVs
{
    return 0;
}

void Speciale::setMultiplicateur(int multi){}//Setter pour le multiplicateur de d�g�ts, utile seulement pour les dirigeants en cours de partie

std::string Speciale::getNature()//Getter pour la nature
{
    return m_nature;
}

Pouvoir Speciale::getPouvoir()//Getter pour le Pouvoir, n�cessaire pour les autres classes filles
{
    Pouvoir p;
    return p;
}

int Speciale::attaquer(int numAttaq)//M�thode utile pour les dirigeants en cours de partie
{
    return 0;
}

int Speciale::subir(int nbDegats)//M�thode utile pour les dirigeants en cours de partie
{
    return 0;
}

void Speciale::affichage() const//Affichage de la carte
{
    std::cout<<"*****SPECIALE*****"<<std::endl;
    std::cout<<"NOM : "<<m_nom<<std::endl;
    std::cout<<"EFFET : "<<m_effet<<std::endl;
    std::cout<<"PERSISTANCE : "<<m_persistance<<std::endl<<std::endl;
}

std::string Speciale::ecriture()//Ecriture de la carte dans un fichier
{
    std::string ecriture = "SPECIALE\n";
    ecriture += m_nom + "\n";
    ecriture += m_effet + "\n";
    ecriture += m_persistance + "\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    return ecriture;
}

std::vector<std::string> Speciale::graphisme() const //Envoie de toutes les informations pour affichage graphique avec Allegro
{
    std::vector<std::string> infos;
    infos.push_back("Effet :");
    infos.push_back(m_effet);
    infos.push_back("Persistance : ");
    infos.push_back(m_persistance);
    return infos;
}
