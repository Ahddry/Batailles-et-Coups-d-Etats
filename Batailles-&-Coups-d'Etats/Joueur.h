#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include "Cartes.h"
#include "Deck.h"
#include <vector>
#include "Terrain.h"
class Joueur
{
private:
    std::string m_pseudo;       //pseudo du joueur
    std::string m_mdp;          //mot de passe du joueur
    std::string m_dossier;      //chemin d'accès du dossier joueur
    std::string m_fichier;      //chemin d'accès du fichier joueur
    int m_money;                //argent du joueur
    std::vector<std::string> m_info;//information du joueur
    bool m_connecter;           //verification si le joueur est connecté
    bool m_quitter;             //verification si le joueur veut quitter
    Deck m_deckJoueur;          //deck du joueur
    Deck m_collection;          //collection du joueur
    Terrain m_plato;
public:
    Joueur();
    Joueur(std::string pseudo, Terrain t);
    ~Joueur();
    std::string getDossier() const; //getter chemin d'accès du fichier joueur
    std::string getPseudo() const;  //getter pseudo du joueur
    void addMoney(int newmoney);    //ajouter de l'argent au joueur
    void removeMoney(int newmoney); //enlever de l'argent au joueur
    int getMoney() const;           //getter de l'argent du joueur
    void saveFichier();             //sauvegarder le ficher
    bool getConnecter() const;      //getter si le joueur est connecté
    bool getQuitter() const;        //getter si le joueur veut quitter
    Deck getDeck() const;           //getter du deck du joueur
    Deck getCollection() const;     //getter de la collection du joueur
    void actualiserDeck();
};


#endif // JOUEUR_H_INCLUDED
