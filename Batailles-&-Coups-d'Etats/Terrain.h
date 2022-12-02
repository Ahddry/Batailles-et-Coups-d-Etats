#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED
#include "Deck.h"
#include "Cartes.h"
#include "Energie.h"
#include "Dirigeant.h"
#include "Speciale.h"
#include <vector>
#include <allegro.h>
#include <png.h>
#include <loadpng.h>
#include <jpgalleg.h>
#include <time.h>
#include <string>

class Terrain
{
private:
    Carte* m_dirigeant1;    //dirigeant du joueur 1 sur le terrain
    Carte* m_dirigeant2;    //dirigeant du joueur 2 sur le terrain
    BITMAP *m_background;   //image de fond de l'affichage
    BITMAP *m_pioche;       //image d'une pile de cartes
    BITMAP *m_plato;        //Bitmap servent de buffer pour l'affichage
    BITMAP *m_energie;      //image du parchemin dans lequel sont affichés les pouvoirs des joueurs
    BITMAP *m_frameDir;     //carte vide
    BITMAP *m_console;      //arrière plan de la console de dialogue avec l'utilisateur en cours de partie
    BITMAP *m_pancarte;     //pancarte sur laquelle sont affichés les points de vies des joueurs
    MIDI* m_musique;        //musique d'ambiance au format MIDI, par Alexander Nakarada
    std::vector<int> m_pouvoir1;//stockage des énergies du joueur 1
    std::vector<int> m_pouvoir2;//stockage des énergies du joueur 2
    std::vector<std::string> m_textEnergie;//texte à afficher avec les énergies
    std::string m_pvJ1;     //Points de vies du premier joueur
    std::string m_pvJ2;     //Points de vies du deuxième joueur
public:
    Terrain();
    Terrain(std::string init);//Initialisation du mode graphique avec tout ses prérequis
    ~Terrain();
    void setup();           //affichage des éléments de base d'une partie
    BITMAP * load_bitmap_check(std::string nomImage);//Méthode du chargement d'une image en vérifiant son existance, obtenue sur le site de M. Fercoq
    void affCarte(int coordX, int coordY, Carte* carte);//Affichage d'une carte donnée à des coordonées x et y données sur le plateau de jeu
    std::vector<std::string> text(std::string str);//Méthode permettant de séparer une chaîne de charactères en 2 aux endroits comprenant un #, obtenue sur cppplusplus.com
    void setDirigeant1(Carte* dir1);//setter pour le dirigeant actif du joueur 1
    void setDirigeant2(Carte* dir2);//setter pour le dirigeant actif du joueur 2
    void setPouvoirs(std::vector<int> pouvoir1, std::vector<int> pouvoir2);//setter pour les stockages d'énergies/pouvoirs de chaque joueur
    void setPv(std::string pseudo1, std::string pseudo2, int pv1, int pv2);//setter pour les pv de chaque joueur
    void afficher();        //affichages des éléments du buffer
    int texteConsole(std::vector<std::string> texte, int nbChoix);//écriture d'un texte et choix par l'utilisateur à la souris de quelque chose dans la console de dialogue
    void emphase(std::string titre, std::string sousTitre);//Message accentué avec une première chose écrite en gros et une seconde en un peu plus petit en dessous
    void piocher(std::string pseudo, int nbJoueur);//demande à un des deux joueurs de cliquer sur son deck pour mimer un piochage de carte
    void endgame(Carte* enjeu1, Carte* enjeu2, std::string pseudo);//affichage des cartes tirées comme enjeu gagnées par le vainqueur
    void partie(Carte* dirigeant1, Carte* dirigeant2);//initialisation d'une partie de jeu
    int menu(std::string titre, std::vector<std::string> choix, int nbChoix);//menu divers avec choix paramétrables, attendant un clic de l'utilisateur sur une des options proposées
    std::string saisie(std::string titre, std::string texte);//saisie similaire à un "std::getline(std::cin, variable)" de l'utilisateur, pour allegro
    void effacer();         //effacer tous les éléments actuellement en buffer
    void erreur(std::string msg);//message d'erreur en rouge au bas de l'écran
    int menuPrincipal();    //Menu principal du jeu, attendant un clic de l'utilisateur sur une des options proposées
    int menuExtras();       //Menu des extensions du jeu, attendant un clic de l'utilisateur sur une des options proposées
    void affDeck(Deck deck, unsigned int page);//Méthode d'affichage d'un grand deck sur plusieurs page de 5 cartes
    void argent(int argent);//affichage des coins du joueur en bas à droite de l'écran
    void regles(std::vector<std::string> regles);//affichage des règles ou des crédits sur un panneau au dessus du menu principal
    void standby();         //attente que l'utilisateur clique sur fermer ou appuie sur [ECHAP]
};
#endif // TERRAIN_H_INCLUDED
