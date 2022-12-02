#ifndef SPECIALE_H_INCLUDED
#define SPECIALE_H_INCLUDED
#include "Cartes.h"
#include "Pouvoir.h"
#include <string>
#include <vector>
///Classe g�rant toutes les cartes "Sp�ciales", alt�rant le jeu
class Speciale : public Carte
{
private:
    std::string m_effet;        //Description de l'effet de la carte
    std::string m_persistance;  //Indication sur la dur�e d'effet de la carte
public:
    Speciale();
    Speciale(std::string nom, std::string effet, std::string persistance);
    ~Speciale();

    std::string getNom() const;         //Getter pour le nom
    int getPV() const;                  //Getter pour les PVs
    void setMultiplicateur(int multi);  //Setter pour le multiplicateur de d�g�ts, utile seulement pour les dirigeants en cours de partie
    std::string getNature();            //Getter pour la nature
    Pouvoir getPouvoir();               //Getter pour le Pouvoir, n�cessaire pour les autres classes filles de cartes
    int attaquer(int numAttaq);         //M�thode utile pour les dirigeants en cours de partie
    int subir(int nbDegats);            //M�thode utile pour les dirigeants en cours de partie
    void affichage() const;             //Affichage de la carte
    std::string ecriture();             //Ecriture de la carte dans un fichier
    std::vector<std::string> graphisme() const; //Envoie de toutes les informations pour affichage graphique avec Allegro
};

#endif // SPECIALE_H_INCLUDED
