#ifndef ATTAQUE_H_INCLUDED
#define ATTAQUE_H_INCLUDED
#include "Pouvoir.h"
#include <string>
#include <vector>
///Classe gérant les attaques des dirigeants
class Attaque
{
private:
    std::string m_nom;              //Nom de l'attaque
    std::vector<Pouvoir> m_pouvoir; //Points de pouvoir nécéssaire à l'activation de l'attaque
    int m_degat;                    //Points de dégâts de base de l'attque
    int m_multiplicateur;           //Multiplicateur de dégâts actif
public:
    Attaque();
    Attaque(std::string nom, std::vector<Pouvoir> p, int degat);
    ~Attaque();
    void afficher() const;          //Affichage de l'attaque
    std::string getAttaque() const; //Mise en forme pour écriture dans un fichier
    std::vector<std::string> graphAttaque() const; //Mise en forme pour affichage graphique
    void setMultiplicateur(int multi);//Setter pour le multiplicateur de dégâts
};

#endif // ATTAQUE_H_INCLUDED
