#include "Energie.h"
#include "Cartes.h"
#include "Pouvoir.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

Energie::Energie(std::string nom, Pouvoir type, std::string texte)  ///Creation d'une carte Energie en donnant son nom, son type et son texte descriptif
    : Carte(nom, "Energie"), m_type(type), m_texte(texte){}
Energie::~Energie(){}

std::string Energie::getNom() const//Getter pour le nom
{
    return m_nom;
}

int Energie::getPV() const//Getter pour les PVs
{
    return 0;
}
void Energie::setMultiplicateur(int multi){}//Setter pour le multiplicateur de dégâts, utile seulement pour les dirigeants en cours de partie
std::string Energie::getNature()//Getter pour la nature
{
    return m_nature;
}
Pouvoir Energie::getPouvoir()//Getter pour le Pouvoir, retournant le type de la carte
{
    return m_type;
}
int Energie::attaquer(int numAttaq)//Méthode utile pour les dirigeants en cours de partie
{
    return 0;
}
int Energie::subir(int nbDegats)//Méthode utile pour les dirigeants en cours de partie
{
    return 0;
}
void Energie::affichage() const//Affichage de la carte
{
    std::cout<<"*****ENERGIE*****"<<std::endl;
    std::cout<<"NOM : "<<m_nom<<std::endl;
    std::cout<<"POUVOIR : ";
    m_type.afficher();
    std::cout<<std::endl;
    std::cout<<m_texte<<std::endl<<std::endl;;
}


std::string Energie::ecriture()//Ecriture de la carte dans un fichier
{
    std::string ecriture = "ENERGIE\n";
    ecriture += m_nom + "\n";
    ecriture += m_type.getNom() + "\n";
    ecriture += m_texte + "\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    ecriture += "vide\n";
    return ecriture;
}

std::vector<std::string> Energie::graphisme() const //Envoie de toutes les informations pour affichage graphique avec Allegro
{
    std::vector<std::string> infos;
    infos.push_back("Type : ");
    infos.push_back(m_type.getNom());
    infos.push_back("Legende :");
    infos.push_back(m_texte);
    return infos;
}
