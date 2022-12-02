#include "Pouvoir.h"
#include <string>
#include <iostream>

Pouvoir::Pouvoir(){}

Pouvoir::Pouvoir(std::string type)  ///Construction d'un pouvoir en fournissant son nom
{
    if(type=="Politique"||type=="Economique"||type=="Militaire"||type=="Religieux"||type=="Any") //Verification de si le pouvoir existe dans le jeu
    {
        m_type=type;
    }
    else
    {
        std::cout << "Erreur de pouvoir\n";
    }
}

Pouvoir::~Pouvoir(){}

void Pouvoir::afficher() const      //Affichage du pouvoir
{
    std::cout<<m_type;
}

std::string Pouvoir::getNom() const //Retour du pouvoir sous forme de chaîne de charactères
{
    return m_type;
}
