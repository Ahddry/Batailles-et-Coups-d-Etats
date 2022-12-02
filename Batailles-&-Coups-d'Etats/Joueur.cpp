#include "Joueur.h"
#include "Deck.h"
#include "Scores.h"
#include <fstream>
#include <string>
#include <direct.h> //pour l'instruction mkdir
#include <iostream>
#include <vector>
#include <time.h>


Joueur::Joueur(){}///constructeur par défaut d'un joueur
Joueur::Joueur(std::string pseudo, Terrain t) : m_plato(t)///constructeur d'un joueur prenant en enter le pseudo du joueur deja connecté
{
    m_plato.effacer();
    m_quitter=false;
    m_connecter =false;
    while(m_connecter==false)
    {
        std::vector<std::string> propos;    //proposition à afficher à l'utilisateur souhaitant accéder à un compte
        propos.push_back("Se connecter");
        propos.push_back("Creer un compte");
        propos.push_back("Quitter");
        int rep = m_plato.menu("Menu Connexion", propos, 3);//choix du joueur
        switch(rep)
        {
        case 1:///pour choix se connecter
            {
                m_plato.effacer();
                m_pseudo = m_plato.saisie("Connexion", "Nom d'utilisateur :");//recuperation du pseudo
                m_dossier="Joueur/"+m_pseudo+"/";//recuperation du chemin d'accès du dossier joueur
                if(m_pseudo!=pseudo)//verification si le joueur n'est pas deja connecté
                {
                    m_fichier= "Joueur/"+m_pseudo+"/"+m_pseudo+".txt";//recuperation du chemin d'accès du fichier joueur
                    std::ifstream fichierJoueur(m_fichier);//ouverture d'un flux de lecture vers le fichier joueur
                    if(fichierJoueur)//si le fichier existe
                    {
                        m_plato.effacer();
                        m_mdp = m_plato.saisie("Connexion", "Mot de passe :");//récupération du mot de passe du joueur
                        std::string ligne;
                        while(getline(fichierJoueur, ligne))//lecture du fichier et enregistrement dans le tableau d'info joueur
                        {
                            m_info.push_back(ligne);
                        }
                        if(m_info[1]==m_mdp)//si le mot de passe est bon
                        {
                            m_connecter =true;
                        }
                        else//si le mot de passe est incorrect
                        {
                            m_plato.erreur("Mot de passe incorrect!");
                        }
                    }
                    else//si le nom d'utilisateur n'existe pas
                    {
                        m_plato.erreur("Erreur: Le nom d'utilisateur n'existe pas!");
                    }
                }
                else//si le joueur est deja connecte
                {
                    m_plato.erreur("Ce joueur est deja connecte!");
                }
                std::string const emplDeck = m_dossier+"Deck.txt";
                std::string const emplCollection = m_dossier+"Collection.txt";
                Deck newDeck(emplDeck);
                m_deckJoueur = newDeck;//récupération du deck du joueur
                Deck newCol(emplCollection);
                m_collection = newCol;//récupération de la collection du joueur
                break;
            }
        case 2:///pour choix créer un compte
            {
                m_plato.effacer();
                bool usernameTake=false;
                while(usernameTake==false)
                {
                    m_pseudo = m_plato.saisie("Creation de compte", "Nom d'utilisateur :");//récupération du choix du joueur;
                    m_fichier= "Joueur/"+m_pseudo+"/"+m_pseudo+".txt";//récupération du chemin d'accès du fichier du joueur
                    std::ifstream fichierJoueur(m_fichier.c_str());
                    if(fichierJoueur)//si le fichier existe
                    {
                        m_plato.erreur("Erreur: Le nom d'utilisateur existe deja!");
                        usernameTake=false;
                    }
                    else
                    {
                        usernameTake=true;
                    }
                }
                m_mdp = m_plato.saisie("Creation de compte", "Mot de passe :");//récupération du mot de passe choisi
                m_dossier="Joueur/"+m_pseudo+"/";//récupération du chemin d'accès du dossier joueur
                mkdir(m_dossier.c_str());//création d'un dossier pour le joueur
                m_fichier=m_dossier+m_pseudo+".txt";
                std::ifstream testFichierJoueur(m_fichier.c_str());
                if(testFichierJoueur)//vérification si le fichier n'existe pas déja
                {
                    m_plato.erreur("Le fichier existe deja");
                }
                else
                {
                    std::ofstream fichierJoueur(m_fichier.c_str());
                    if(fichierJoueur)//ecriture du fichier joueur
                    {
                        fichierJoueur << m_pseudo<< std::endl;//ligne 1 pseudo
                        fichierJoueur << m_mdp<< std::endl;//ligne 2 mot de passe
                        fichierJoueur <<"0"<< std::endl;//ligne 3 argent du joueur
                        m_money=0;//enregistrement de l'argent du joueur
                    }
                    else
                    {
                        m_plato.erreur("Erreur ouverture du fichier impossible");
                    }
                }
                Scores scores(t);
                scores.ajoutJoueur(m_pseudo);
                std::string const emplacementDeck = m_dossier+"Deck.txt";
                std::string const emplacementCol = m_dossier+"Collection.txt";
                Deck newDeck("Deck de base.txt");       //Création des nouveaux decks et collection à partir du deck de base, un deck relativement faible
                m_deckJoueur = newDeck;                 //permettant de jouer des parties équilibrées entre débutants
                m_collection = newDeck;
                m_deckJoueur.ecrireDeck(emplacementDeck);//récupération du deck du joueur
                m_collection.ecrireDeck(emplacementCol);//récupération de la collection du joueur
                m_connecter = true;//joueur connecté
                break;
            }
        case 3:///si choix est quitter
            {
                m_quitter=true;
                m_connecter=true;
                break;
            }

        }
    }
    if(m_quitter==true)//si choix de quitter
    {
        m_plato.effacer();
        m_plato.emphase("", "Bonne journee.");
        rest(400);
    }
    else
    {
        m_plato.emphase("Bienvenue", m_pseudo + " !");
        std::ifstream fichierJoueur(m_fichier.c_str());
        if(fichierJoueur)//lecture des information du joueur
        {
            std::string ligne;
            while(getline(fichierJoueur, ligne))
            {
                m_info.push_back(ligne);
            }
        }
        else
        {
        m_plato.erreur("Erreur: Le fichier n'existe pas!");
        }
        m_money=std::stoi(m_info[2]);
        rest(600);
    }
}
Joueur::~Joueur(){}///Destructeur Joueur
std::string Joueur::getDossier() const//retourne du chemin d'accès du fichier sous forme de chaine de caractère
{
    return m_dossier;
}
void Joueur::addMoney(int newmoney)//Ajoute l'argent donnée en entrée au joueur
{
    m_money+=+newmoney;
    saveFichier();
}
void Joueur::removeMoney(int newmoney)//Enleve l'argent donnée en entrée au joueur
{
    m_money-=newmoney;
    saveFichier();
}
int Joueur::getMoney() const//retourne l'argent du joueur
{
    return m_money;
}
void Joueur::saveFichier()//sauvegarde le fichier du joueur
{
    std::ofstream fichierJoueur(m_fichier.c_str());
    if(fichierJoueur)
    {
        fichierJoueur << m_info[0]<< std::endl;
        fichierJoueur << m_info[1]<< std::endl;
        fichierJoueur <<m_money<< std::endl;
    }
    else
    {
        m_plato.erreur("Erreur ouverture du fichier impossible");
    }
}

std::string Joueur::getPseudo() const//retourne le pseudo du joueur sous forme de chaine de caractère
{
    return m_pseudo;
}
bool Joueur::getConnecter() const//retourne si le joueur est connecté sous forme d'un bool
{
    return m_connecter;
}
bool Joueur::getQuitter() const//retourne si le joueur veux quitter sous forme d'un bool
{
    return m_quitter;
}
Deck Joueur::getDeck() const//retourne le deck du joueur
{
    return m_deckJoueur;
}
Deck Joueur::getCollection() const//retourne la collection du joueur
{
    return m_collection;
}
void Joueur::actualiserDeck()//Actualise les deck et collection du joueur en cas de changements
{
    std::string const emplDeck = m_dossier+"Deck.txt";
    std::string const emplCollection = m_dossier+"Collection.txt";
    Deck newDeck(emplDeck);
    m_deckJoueur = newDeck;//récupération du deck du joueur
    Deck newCol(emplCollection);
    m_collection = newCol;//récupération de la collection du joueur
}
