#ifndef ATTAQUE_H_INCLUDED
#define ATTAQUE_H_INCLUDED
#include "Pouvoir.h"
#include <string>
#include <vector>
///Classe g�rant les attaques des dirigeants
class Attaque
{
private:
    std::string m_nom;              //Nom de l'attaque
    std::vector<Pouvoir> m_pouvoir; //Points de pouvoir n�c�ssaire � l'activation de l'attaque
    int m_degat;                    //Points de d�g�ts de base de l'attque
    int m_multiplicateur;           //Multiplicateur de d�g�ts actif
public:
    Attaque();
    Attaque(std::string nom, std::vector<Pouvoir> p, int degat);
    ~Attaque();
    void afficher() const;          //Affichage de l'attaque
    std::string getAttaque() const; //Mise en forme pour �criture dans un fichier
    std::vector<std::string> graphAttaque() const; //Mise en forme pour affichage graphique
    void setMultiplicateur(int multi);//Setter pour le multiplicateur de d�g�ts
};

#endif // ATTAQUE_H_INCLUDED
