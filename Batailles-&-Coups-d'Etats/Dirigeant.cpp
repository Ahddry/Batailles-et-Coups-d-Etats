#include "Dirigeant.h"
#include "Cartes.h"
#include "Attaque.h"
#include "Pouvoir.h"
#include <string>
#include <iostream>
#include <fstream>

Dirigeant::Dirigeant(): Carte("Sans nom", "Dirigeant"), m_PV(0){}   ///Constructeur par défaut pour un dirigeant

Dirigeant::Dirigeant(std::string nom, int pv, Attaque attaq1, Attaque attaq2, Pouvoir type) ///Creation d'un Dirigeant en donnant son nom, ses PV, ses attaques et son type
    : Carte(nom, "Dirigeant"), m_PV(pv), m_attaque1(attaq1), m_attaque2(attaq2), m_type(type), m_multiplicateur(1)
    {}
Dirigeant::~Dirigeant(){}

std::string Dirigeant::getNom() const//Getter pour le nom
{
    return m_nom;
}

int Dirigeant::getPV() const//Getter pour les PVs
{
    return m_PV;
}
void Dirigeant::setMultiplicateur(int multi)//Setter pour le multiplicateur de dégâts
{
    if(multi>0)
    {
        m_multiplicateur *= multi;          //Augmentation du multiplicateur
    }
    else
    {
        multi*=(-1);
        m_multiplicateur /= multi;          //Réduction du multiplicateur
    }
    m_attaque1.setMultiplicateur(m_multiplicateur);//Set les multiplicateurs dans l'affichage des attaques
    m_attaque2.setMultiplicateur(m_multiplicateur);
}
int Dirigeant::attaquer(int numAttaq)//Retourne le nombre de dégâts infligés en fonction de l'attque choisie et du multiplicateur de dégâts actif
{
    if(numAttaq == 1)
    {
        return 1*m_multiplicateur;
    }
    else
    {
        return 3*m_multiplicateur;
    }
}
int Dirigeant::subir(int nbDegats)//Methode pour infliger des dégâts au dirigeants, retournant la différence si ce nombre est supérieur au nombre de PVs du dirigeant
{
    if(m_PV-nbDegats>=0)
    {
        m_PV-=nbDegats;
        return 0;
    }
    else
    {
        m_PV-=nbDegats;
        int difference = (-1)*m_PV;
        m_PV = 0;
        return difference;
    }
}

std::string Dirigeant::getNature()//Getter pour la nature
{
    return m_nature;
}
Pouvoir Dirigeant::getPouvoir()//Getter pour le type
{
    return m_type;
}
void Dirigeant::affichage() const//Affichage de la carte
{
    std::cout<<"*****DIRIGEANT*****"<<std::endl;
    std::cout<<"NOM : "<<m_nom<<std::endl;
    std::cout<<"PV : "<<m_PV<<std::endl;
    std::cout<<"ATTAQUE 1 : "<<std::endl;
    m_attaque1.afficher();
    std::cout<<"ATTAQUE 2 : "<<std::endl;
    m_attaque2.afficher();
    std::cout<<"TYPE : ";
    m_type.afficher();
    std::cout<<std::endl<<std::endl;;
}


std::string Dirigeant::ecriture()//Ecriture de la carte dans un fichier
{
    std::string ecriture = "DIRIGEANT\n";
    ecriture += m_nom + "\n";
    ecriture += std::to_string(m_PV) + "\n";
    ecriture += m_attaque1.getAttaque();
    ecriture += m_attaque2.getAttaque();
    ecriture += m_type.getNom() + "\n";
    return ecriture;
}

std::vector<std::string> Dirigeant::graphisme() const //Envoie de toutes les informations pour affichage graphique avec Allegro
{
    std::vector<std::string> infos;
    infos.push_back("PV :          "+std::to_string(m_PV));
    infos.push_back("Attaque 1 :");
    for(const auto elem:m_attaque1.graphAttaque())
    {
        infos.push_back(elem);
    }
    infos.push_back("Attaque 2 :");
    for(const auto chose:m_attaque2.graphAttaque())
    {
        infos.push_back(chose);
    }
    infos.push_back(m_type.getNom());
    return infos;
}
