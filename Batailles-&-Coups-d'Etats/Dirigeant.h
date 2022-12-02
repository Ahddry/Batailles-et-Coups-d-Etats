#ifndef DIRIGEANT_H_INCLUDED
#define DIRIGEANT_H_INCLUDED
#include "Cartes.h"
#include "Attaque.h"
#include "Pouvoir.h"
#include <string>
///Classe g�rant toutes les cartes "Monstre" ou "Dirigeant"
class Dirigeant: public Carte
{
private:
    int m_PV;                   //Points de vie du dirigeant
    Attaque m_attaque1;         //Premi�re attaque du dirigeant
    Attaque m_attaque2;         //Seconde attaque du dirigeant
    Pouvoir m_type;             //Type du dirigeant
    int m_multiplicateur;       //Multiplicateur de d�g�t actif
public:
    Dirigeant();
    Dirigeant(std::string nom, int pv, Attaque attaq1, Attaque attaq2, Pouvoir type);
    ~Dirigeant();

    std::string getNom() const; //Getter pour le nom
    int getPV() const;          //Getter pour les PVs
    void setMultiplicateur(int multi); //Setter pour le multiplicateur de d�g�ts
    int attaquer(int numAttaq);         //Retourne le nombre de d�g�ts inflig�s en fonction de l'attque choisie et du multiplicateur de d�g�ts actif
    int subir(int nbDegats);            //Methode pour infliger des d�g�ts au dirigeants, retournant la diff�rence si ce nombre est sup�rieur au nombre de PVs du dirigeant
    std::string getNature();            //Getter pour la nature
    Pouvoir getPouvoir();               //Getter pour le type
    void affichage() const;             //Affichage de la carte
    std::string ecriture();             //Ecriture de la carte dans un fichier
    std::vector<std::string> graphisme() const; //Envoie de toutes les informations pour affichage graphique avec Allegro
};

#endif // DIRIGEANT_H_INCLUDED
