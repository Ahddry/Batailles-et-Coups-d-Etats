#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED
#include "Pouvoir.h"
#include <string>
#include <vector>

///Classe m�re g�rant de mani�re virtuelle tous les types de cartes diff�rents
class Carte
{
protected:
    std::string m_nom;          //Nom de la carte
    std::string m_nature;       //Nature de la carte (Dirigeant, Energie ou Sp�ciale)
public:
    Carte();
    Carte(std::string nom, std::string nature);
    virtual ~Carte();

    virtual std::string getNom() const;         //Getter pour le nom
    virtual int getPV() const;                  //Getter pour les PVs
    virtual void setMultiplicateur(int multi);  //Setter pour le multiplicateur de d�g�ts, utile seulement pour les dirigeants en cours de partie
    virtual std::string getNature();            //Getter pour la nature
    virtual Pouvoir getPouvoir();               //Getter pour le Pouvoir, n�cessaire pour les classes filles
    virtual int attaquer(int numAttaq);         //M�thode utile pour les dirigeants en cours de partie
    virtual int subir(int nbDegats);            //M�thode utile pour les dirigeants en cours de partie
    virtual void affichage() const;             //Affichage de la carte
    virtual std::string ecriture();             //Ecriture de la carte dans un fichier
    virtual std::vector<std::string> graphisme() const; //Envoie de toutes les informations pour affichage graphique avec Allegro
};



#endif // CARTES_H_INCLUDED
