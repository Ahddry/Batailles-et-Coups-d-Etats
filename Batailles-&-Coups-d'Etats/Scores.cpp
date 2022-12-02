#include "Scores.h"
#include <fstream>
#include <iostream>

Scores::Scores(Terrain t) : m_terrain(t)
{
    m_fichier = "Joueur/scores.txt";       //emplacement du fichier
    std::vector<std::string> vec;
    std::ifstream scores(m_fichier.c_str());//lecture du fichier
    if(scores)
    {
        std::string ligne;
        while(getline(scores, ligne))
        {
            vec.push_back(ligne);
        }
        for(const auto& elem:vec)       ///morceau de code issu de cplusplus.com, voir plus en détail dans la méthode Texte de la classe Terrain
        {
            std::size_t pos = elem.find(" ");      //position de " " dans elem
            std::string str1 = elem.substr(0, pos);
            int int1 = atoi(elem.substr(pos).c_str());
            m_joueurs.push_back(str1);  //Ajout du joueur au tableau des joueurs
            m_victoires.push_back(int1);//Ajout de son nombre de victoire actuel
        }
        tri();
    }
    else
    {
        m_terrain.erreur("Erreur: Le fichier n'existe pas!");
    }
}
Scores::~Scores(){}

void Scores::save()             ///Sauvegarde du fichier
{
    std::ofstream scores(m_fichier.c_str());
    if(scores)
    {
        for(unsigned int i=0; i<m_joueurs.size(); i++)
        {
            scores << m_joueurs[i] + " " + std::to_string(m_victoires[i]) << std::endl;;
        }
    }
    else
    {
        m_terrain.erreur("Erreur ouverture du fichier impossible");
    }
}

void Scores::ajoutVictoire(std::string joueur)  ///Ajout d'une victoire au compteur pour un joueur donné
{
    for(unsigned int i=0; i<m_joueurs.size(); i++)
    {
        if(m_joueurs[i]==joueur) m_victoires[i] ++;
    }
    tri();
    save();
}

void Scores::ajoutJoueur(std::string joueur)    ///Ajout d'un joueur au fichier
{
    m_joueurs.push_back(joueur);
    m_victoires.push_back(0);
    save();
}

void Scores::tri()                              ///Tri des tableaux par ordre du joueur ayant le plus de victoires
{
    if (m_joueurs.size() == m_victoires.size())
    {
        bool tri = false;
        while (tri == false)
        {
            tri = true;
            for (unsigned int i = 0; i < m_joueurs.size() - 1; i++)
            {
                if (m_victoires[i] < m_victoires[i + 1])
                {
                    std::string inter = m_joueurs[i];
                    m_joueurs[i] = m_joueurs[i + 1];
                    m_joueurs[i + 1] = inter;
                    int temp = m_victoires[i];
                    m_victoires[i] = m_victoires[i + 1];
                    m_victoires[i + 1] = temp;
                    tri = false;
                }
            }
        }
    }
    else m_terrain.erreur("Erreur taille tableau");
}

void Scores::affichage() ///Affichage des 7 meilleurs joueurs du jeu
{
    std::vector<std::string> vec;
    for(unsigned int i=0; i<7; i++)
    {
        vec.push_back(m_joueurs[i] + "     " + std::to_string(m_victoires[i]));
    }
    m_terrain.menu("Meilleurs joueurs", vec, 0);
    m_terrain.standby();
}
