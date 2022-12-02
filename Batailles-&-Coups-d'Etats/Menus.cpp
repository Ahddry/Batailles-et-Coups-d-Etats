#include "Menus.h"
#include <string>
#include <vector>
#include <fstream>
#include "Scores.h"

Menus::Menus(Terrain t) : m_terrain(t)
{
    Joueur j("", m_terrain);
    m_joueur = j;
}
Menus::~Menus(){}

bool Menus::principal()///Menu principal du jeu
{
    bool quit = false;
    bool fin = false;
    m_terrain.effacer();
    m_joueur.actualiserDeck();//actualisation de la collection et du deck du joueur connecté
    int choix;
    if(m_joueur.getQuitter()) choix = 7;    //Si l'utilisateur à choisi de ne pas se connecter ou de ne pas créer de compte
    else
    {
        choix = m_terrain.menuPrincipal();  //Selection du choix de l'utilisateur et affichage du menu
    }
    switch(choix)
    {
    case 1:
    {
        Joueur j2(m_joueur.getPseudo(), m_terrain); //Connection d'un deuxième joueur
        if(j2.getQuitter()) m_terrain.erreur("Il faut deux joueurs pour jouer une partie.");
        else
        {
            Jeu game(m_joueur, j2, m_terrain);
            game.deroulementJeu();              //Lancement d'une partie
        }
        break;
    }
    case 2:
    {
        ///Règles
        std::vector<std::string> regles;
        std::ifstream fichierRegles("Regles.txt");//ouverture d'un flux de lecture vers le fichier des règles
        if(fichierRegles)//si le fichier existe
        {
            std::string ligne;
            while(getline(fichierRegles, ligne))//lecture du fichier ligne par ligne
            {
                regles.push_back(ligne);
            }
            m_terrain.regles(regles);           //Affichage des règles
        }
        else//si le fichier n'existe pas
        {
            m_terrain.erreur("Erreur: Le fichier n'existe pas!");
        }
        break;
    }
    case 3:
    {
        ///Concepteur de deck
        Switch s(m_joueur, m_terrain);  //ouverture du sous-menu de conception de deck
        break;
    }
    case 4:
    {
        ///Boutique
        Boutique b(m_joueur, m_terrain);//ouverture de la boutique
        break;
    }
    case 5:
    {
        ///Crédits
        std::vector<std::string> credits;
        std::ifstream fichierCredits("Credits.txt");//ouverture d'un flux de lecture vers le fichier des crédits
        if(fichierCredits)//si le fichier existe
        {
            std::string ligne;
            while(getline(fichierCredits, ligne))//lecture du fichier ligne par ligne
            {
                credits.push_back(ligne);
            }
            m_terrain.regles(credits);          //affichage des crédits
        }
        else//si le fichier n'existe pas
        {
            m_terrain.erreur("Erreur: Le fichier n'existe pas!");
        }
        break;
    }
    case 6:
        ///Sous menu extras
        while(!fin)
        {
            fin = extras();
        }
        break;
    case 7 :
        ///Quitter
        quit = true;
        break;
    default:
        m_terrain.erreur("Choix non existant.");
        break;
    }
    return quit;
}

bool Menus::extras()///Menu des extensions
{
    bool quit = false;
    bool fin = false;
    m_terrain.effacer();
    m_joueur.actualiserDeck();//actualisation de la collection et du deck du joueur connecté
    int choix;
    choix = m_terrain.menuExtras();//Selection du choix de l'utilisateur et affichage du menu
    switch(choix)
    {
    case 1:
        ///Creer des cartes
        while(!fin)
        {
            fin = creationCarte();//sous-menu de création de cartes
        }
        break;
    case 2:
    {
        ///Top joueurs
        Scores s(m_terrain);    //Affichage des 7 meilleurs joueurs du jeu
        s.affichage();
        break;
    }
    case 3 :
        ///Quitter
        quit = true;
        break;
    default:
        m_terrain.erreur("Choix non existant.");
        break;
    }
    return quit;
}

bool Menus::creationCarte()///menu de l'extension de création de cartes
{
    m_terrain.effacer();
    bool fin = false;
    std::vector<std::string> propos;//Chargement des propositions du menu
    propos.push_back("Creer une carte Dirigeant");
    propos.push_back("Creer une carte Pouvoir");
    propos.push_back("Retour au menu principal");

    int choix = m_terrain.menu("Createur de cartes", propos, 3);//sélection du choix par l'utilisteur
    switch(choix)
    {
    case 1:    ///lorsque l'utilisateur souhaite créer un Dirieant personalisé, avec un nom, un nombre de PV et des attaques personnalisés
    {
        m_terrain.effacer();
        std::string nom("Sans nom");
        nom = m_terrain.saisie("Outil createur de Dirigeant", "Veuillez saisir le nom de votre dirigeant : ");
        int pv;
        do
        {
            pv = atoi(m_terrain.saisie("Outil createur de Dirigeant", "Veuillez saisir le nombre de Points de Vie de votre dirigeant : ").c_str());
            if(pv<=2){m_terrain.erreur("Le nombre de PV doit etre superieur a 2 !");}
            if(pv>7){m_terrain.erreur("Le nombre de PV maximal est de 7 !");}
        }while(pv<=2||pv>7);
        std::string t;
        std::vector<std::string> propositions;
        propositions.push_back("Militaire");
        propositions.push_back("Religieux");
        propositions.push_back("Economique");
        propositions.push_back("Politique");
        int choix2 = m_terrain.menu("Choisissez le type de votre dirigeant", propositions, 4);
        if(choix2 == 1) t = "Militaire";
        if(choix2 == 2) t = "Religieux";
        if(choix2 == 3) t = "Economique";
        if(choix2 == 4) t = "Politique";
        Pouvoir type(t);
        Attaque attaque1 = attaque(1, type);//Création des attaques
        Attaque attaque2 = attaque(2, type);
        Deck collection("Collection.txt");
        std::vector<Carte*> vec = collection.getDeck();//récupération de la collection universelle existante
        vec.push_back(new Dirigeant(nom, pv, attaque1, attaque2, type));
        Deck collection2(vec);
        collection2.ecrireDeck("Collection.txt");
        break;
    }
    case 2:         ///lorsque l'utilisateur souhaite créer une carte pouvoir personalisé, avec un nom, un type au choix et une description
    {
        m_terrain.effacer();
        std::string nom("Sans nom");
        nom = m_terrain.saisie("Outil createur de cartes Pouvoir", "Veuillez saisir le nom de votre carte de pouvoir : ");
        std::string t;
        std::vector<std::string> propositions;
        propositions.push_back("Militaire");
        propositions.push_back("Religieux");
        propositions.push_back("Economique");
        propositions.push_back("Politique");
        int choix2 = m_terrain.menu("Choisissez le type de votre Pouvoir", propositions, 4);
        if(choix2 == 1) t = "Militaire";
        if(choix2 == 2) t = "Religieux";
        if(choix2 == 3) t = "Economique";
        if(choix2 == 4) t = "Politique";
        Pouvoir type(t);
        std::string texte("Pas de description");
        texte = m_terrain.saisie("Outil createur de cartes Pouvoir", "Veuillez saisir la description votre carte de pouvoir : ");
        Deck collection("Collection.txt");
        std::vector<Carte*> vec = collection.getDeck();//récupération de la collection universelle existante
        vec.push_back(new Energie(nom, type, texte));
        Deck collection2(vec);
        collection2.ecrireDeck("Collection.txt");
        break;
    }
    case 3:
        fin = true;
        break;
    default:
        m_terrain.erreur("Choix non existant.");
        break;
    }
    return fin;
}

Attaque Menus::attaque(int numAttaque, Pouvoir type)    ///Création d'une attaque personnalisé par l'utilisateur pour son dirigeant avec un nom
{
    m_terrain.effacer();
    std::string nom("Sans nom");
    nom = m_terrain.saisie("Outil createur d'Attaque", "Veuillez saisir le nom de votre attaque : ");
    std::vector<Pouvoir> p;
    int degat(0);
    if(numAttaque == 1)
    {
        p.push_back(type);
        degat = 1;
    }
    if(numAttaque == 2)
    {
        p.push_back(type);
        p.push_back(type);
        Pouvoir any("Any");
        p.push_back(any);
        degat = 3;
    }
    Attaque a(nom, p, degat);
    return a;
}
