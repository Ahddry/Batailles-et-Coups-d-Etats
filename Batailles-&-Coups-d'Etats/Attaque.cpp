#include "Attaque.h"
#include <iostream>
Attaque::Attaque(){}        ///Constructeur par défaut d'une attaque

Attaque::Attaque(std::string nom, std::vector<Pouvoir> p, int degat)    ///Creation d'une attaque en donnant son nom et ses pouvoirs ainsi que son nombre de point de dégâts de base
{
    m_nom=nom;
    m_pouvoir=p;
    m_degat = degat;
    m_multiplicateur=1;
}
Attaque::~Attaque(){}

void Attaque::afficher() const        //Affichage de l'attaque
{
    std::cout<<m_nom<<"\t";
    for(const auto& elem:m_pouvoir)
    {
        elem.afficher();
        std::cout<<" ";
    }
    std::cout<<m_degat*m_multiplicateur<<" Points de degat(s)"<<std::endl;
}

std::string Attaque::getAttaque() const //Mise en forme pour écriture dans un fichier
{
    std::string ecriture;
    ecriture += m_nom + "\n";
    for(const auto& elem:m_pouvoir)
    {
        std::string a = elem.getNom();
        ecriture += a + "\n";
    }
    return ecriture;
}

std::vector<std::string> Attaque::graphAttaque() const //Mise en forme pour affichage graphique
{
    std::vector<std::string> graph;
    graph.push_back(m_nom);
    std::string pouv;
    std::string degats;
    for(const auto& elem:m_pouvoir)
    {
        pouv+=elem.getNom() + " ";
    }
    if(pouv.size()<=20) pouv+= std::to_string(m_degat*m_multiplicateur) + " Pts degat(s)";
    else degats = std::to_string(m_degat*m_multiplicateur) + " Pts degat(s)";
    graph.push_back(pouv);
    graph.push_back(degats);
    return graph;
}

void Attaque::setMultiplicateur(int multi)//Setter pour le multiplicateur de dégâts
{
    m_multiplicateur = multi;
}
