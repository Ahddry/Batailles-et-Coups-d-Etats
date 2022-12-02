#ifndef ENERGIE_H_INCLUDED
#define ENERGIE_H_INCLUDED
#include "Cartes.h"
#include "Pouvoir.h"
#include <string>
///Classe gérant toutes les cartes "Energie" ou "Pouvoir"
class Energie: public Carte
{
private:
    Pouvoir m_type;             //Type de la carte Energie (Militaire, Religieu, Economique ou Politique)
    std::string m_texte;        //Texte descriptif de la carte
public:
    Energie(std::string nom, Pouvoir type, std::string texte);
    ~Energie();

    std::string getNom() const;         //Getter pour le nom
    int getPV() const;                  //Getter pour les PVs
    void setMultiplicateur(int multi);  //Setter pour le multiplicateur de dégâts, utile seulement pour les dirigeants en cours de partie
    std::string getNature();            //Getter pour la nature
    Pouvoir getPouvoir();               //Getter pour le Pouvoir, retournant le type de la carte
    int attaquer(int numAttaq);         //Méthode utile pour les dirigeants en cours de partie
    int subir(int nbDegats);            //Méthode utile pour les dirigeants en cours de partie
    void affichage() const;             //Affichage de la carte
    std::string ecriture();             //Ecriture de la carte dans un fichier
    std::vector<std::string> graphisme() const; //Envoie de toutes les informations pour affichage graphique avec Allegro
};

#endif // ENERGIE_H_INCLUDED
