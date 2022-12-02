#include "Jeu.h"
#include "Joueur.h"
#include "Scores.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///Initialistation d'une partie et tirage de l'enjeu en retirant une carte de chaque deck aléatoirement
Jeu::Jeu(Joueur j1, Joueur j2, Terrain plato) : m_terrain(plato)
{
    srand( time(NULL) );        //Choix aléatoire de qui joueura en premier ou en deuxième
    int r = rand() % 2;
    if(r==1)
    {
        Joueur bascule = j2;
        j2 = j1;
        j1 = bascule;
    }
    m_j1 = j1;
    m_j2 = j2;
    m_deck1 = j1.getDeck();     //Récupération des decks
    m_deck2 = j2.getDeck();
    m_deck1.melanger();         //Mélange des decks
    m_deck2.melanger();         //(deux fois pour le deuxième pour le cas où les deux joueurs ont exactement les mêmes decks)
    m_deck2.melanger();
    m_enjeu1 = m_deck1.piocher();//pioche de l'enjeu
    m_enjeu2 = m_deck2.piocher();
    m_pvJ1 = 8;
    m_pvJ2 = 8;
    m_dirigeant1 = new Dirigeant();
    m_dirigeant2 = new Dirigeant();
    m_pouvoir1 = {0,0,0,0};     //Initialisation des Points de Pouvoirs
    m_pouvoir2 = {0,0,0,0};
    m_famine = 0;               //compteur de la carte spéciale "Famine"
    m_francisque = false;
    m_deck1.ecrireDeck(m_j1.getDossier()+"Deck.txt");           //Sauvegarde des decks et collections sans leur enjeu
    m_deck2.ecrireDeck(m_j2.getDossier()+"Deck.txt");
    Deck collection1 = m_j1.getCollection();                    //Chargement des collections de chacun
    Deck collection2 = m_j2.getCollection();
    collection1.retirer(m_enjeu1->getNom());                    //Suppression des cartes enjeu tirées
    collection2.retirer(m_enjeu2->getNom());
    collection1.ecrireDeck(m_j1.getDossier()+"Collection.txt"); //Sauvegarde des collections
    collection2.ecrireDeck(m_j2.getDossier()+"Collection.txt");
    m_terrain.partie(m_dirigeant1, m_dirigeant2);               //Affichage de la partie
    m_terrain.setPv(m_j1.getPseudo(), m_j2.getPseudo(), m_pvJ1, m_pvJ2);
}
Jeu::~Jeu(){}
///Méthode pour l'activation des cartes spéciales
void Jeu::effetSpeciaux(int nbJoueur, std::string nomCarte)
{

    Pouvoir p1 = m_dirigeant1->getPouvoir();
    Pouvoir p2 = m_dirigeant2->getPouvoir();
    std::string type1 = p1.getNom();
    std::string type2 = p2.getNom();
    if(nbJoueur == 1)//Pour le joueur 1
    {
        if(nomCarte=="Mines d'OR")
        {
            if(type1=="Economique") {m_dirigeant1->subir(-2);}      //Les dirigeants economiques gagnent 2 PV.
            if(type2=="Economique") {m_dirigeant2->subir(-2);}
        }
        if(nomCarte=="Trebuchet")
        {
            if(type1=="Militaire") {m_dirigeant1->setMultiplicateur(2);} //Double l'attaque des dirigeants militaires.
            if(type2=="Militaire") {m_dirigeant2->setMultiplicateur(2);}
        }
        if(nomCarte=="Genocide")
        {
            if(type1!="Politique") {m_dirigeant1->subir(2);}        //Les dirigeants non-politiques perdent 2 points de vie.
            if(type2!="Politique") {m_dirigeant2->subir(2);}
        }
        if(nomCarte=="Croisade")
        {
            m_pouvoir1[3] += 3;                                     //Donne 3 Pouvoirs Religieux et 1 Pouvoir Militaire
            m_pouvoir1[0] ++;
            m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
        }
        if(nomCarte=="Peste")
        {
            m_dirigeant1->subir(2);                                 //Tous les dirigeants actifs subissent 2 points de degats.
            m_dirigeant2->subir(2);
        }
        if(nomCarte=="Famine")
        {
            m_famine = 3;                                           //Tous les dirigeants actifs perdent un point de vie pendant 3 tours.
        }
        if(nomCarte=="Francisque")
        {
            m_francisque = true;                                    //Triple l'attaque pendant un tour.
            m_dirigeant1->setMultiplicateur(3);
        }
        if(nomCarte=="Baroud d'honneur")
        {
            m_dirigeant1->subir(2);                                 //Votre dirigeant perd 2PV par deux mais double son attaque.
            m_dirigeant1->setMultiplicateur(2);
        }
    }
    else//Pour le joueur 2
    {
        if(nomCarte=="Mines d'OR")
        {
            if(type1=="Economique") {m_dirigeant1->subir(-2);}      //Les dirigeants economiques gagnent 2 PV.
            if(type2=="Economique") {m_dirigeant2->subir(-2);}
        }
        if(nomCarte=="Trebuchet")
        {
            if(type1=="Militaire") {m_dirigeant1->setMultiplicateur(2);} //Double l'attaque des dirigeants militaires.
            if(type2=="Militaire") {m_dirigeant2->setMultiplicateur(2);}
        }
        if(nomCarte=="Genocide")
        {
            if(type1!="Politique") {m_dirigeant1->subir(2);}        //Les dirigeants non-politiques perdent 2 points de vie.
            if(type2!="Politique") {m_dirigeant2->subir(2);}
        }
        if(nomCarte=="Croisade")
        {
            m_pouvoir2[3] += 3;                                     //Donne 3 Pouvoirs Religieux et 1 Pouvoir Militaire
            m_pouvoir2[0] ++;
        }
        if(nomCarte=="Peste")
        {
            m_dirigeant1->subir(2);                                 //Tous les dirigeants actifs subissent 2 points de degats.
            m_dirigeant2->subir(2);
        }
        if(nomCarte=="Famine")
        {
            m_famine = 6;                                           //Tous les dirigeants actifs perdent un point de vie pendant 3 tours.
        }
        if(nomCarte=="Francisque")
        {
            m_francisque = true;                                    //Triple l'attaque pendant un tour.
            m_dirigeant2->setMultiplicateur(3);
        }
        if(nomCarte=="Baroud d'honneur")
        {
            m_dirigeant2->subir(2);                                 //Votre dirigeant perd 2PV par deux mais double son attaque.
            m_dirigeant2->setMultiplicateur(2);
        }
    }
}

void Jeu::enjeu(int nbJoueur) ///Attribution de l'enjeu au vainqueur
{
    Deck deck(m_vainqueur.getDossier() + "Deck.txt");
    Deck collection(m_vainqueur.getDossier()+"Collection.txt");
    if(nbJoueur==1)
    {
        deck.remettre(m_enjeu1);
    }
    else       //Remise de la carte initialement dans le deck du vaiqueur dans celui-ci, pour une raison de confort lors de la conception des decks
    {
        deck.remettre(m_enjeu2);
    }
    collection.remettre(m_enjeu1);                      //Ajout de l'enjeu à la collection du vainqueur
    collection.remettre(m_enjeu2);
    deck.ecrireDeck(m_vainqueur.getDossier()+"Deck.txt");               //Sauvegarde des deck et collection sur fichier
    collection.ecrireDeck(m_vainqueur.getDossier()+"Collection.txt");
}
///Calcul de la posibilité et des coût d'une attaque
bool Jeu::coutAttaque(int nbAttaque, int nbJoueur, int typeAttaque)
{
    bool possibiliteAttaque = true;
    int typeAny=0;
    if(nbJoueur == 1)//Pour le Joueur 1
    {
        if(nbAttaque==1)    //Pour une attaque 1 qui n'a donc besoin que d'un point de Pouvoir de son type
        {
            if(m_pouvoir1[typeAttaque]>=1)
            {
                m_pouvoir1[typeAttaque]--;
            }
            else
            {
                possibiliteAttaque = false; //Si le joueur n'a pas assez de points de Pouvoir
            }
        }
        else            //Pour une attaque 2 qui a donc besoin de deux points de Pouvoir de son type et d'un point quelconque
        {
            if(m_pouvoir1[typeAttaque]>=2)  //Regarde si le joueur a suffisament de points de Pouvoir de son type
            {
                m_pouvoir1[typeAttaque] -=2;
                typeAny = m_pouvoir1[0] + m_pouvoir1[1] + m_pouvoir1[2] + m_pouvoir1[3];
                if(typeAny>=1)
                {
                    for(unsigned int i=0; i<m_pouvoir1.size(); i++)
                    {
                        if(m_pouvoir1[i]>=1)    //Regarde si le joueur a suffisament de point de Pouvoir quelconque
                        {
                            m_pouvoir1[i]--;
                            break;      //Execution de l'attaque
                        }
                    }
                }
                else                //Si le joueur n'a pas suffisament de point de Pouvoir quelconque
                {
                    m_pouvoir1[typeAttaque] +=2;
                    possibiliteAttaque = false;
                }
            }
            else
            {
                possibiliteAttaque = false;
            }
        }
    }
    else // Pour le joueur 2
    {
        if(nbAttaque==1)            //Pour une attaque 1 qui n'a donc besoin que d'un point de Pouvoir de son type
        {
            if(m_pouvoir2[typeAttaque]>=1)
            {
                m_pouvoir2[typeAttaque]--;
            }
            else
            {
                possibiliteAttaque = false;//Si le joueur n'a pas assez de points de Pouvoir
            }
        }
        else        //Pour une attaque 2 qui a donc besoin de deux points de Pouvoir de son type et d'un point quelconque
        {
            if(m_pouvoir2[typeAttaque]>=2)//Regarde si le joueur a suffisament de points de Pouvoir de son type
            {
                m_pouvoir2[typeAttaque] -=2;
                typeAny = m_pouvoir2[0] + m_pouvoir2[1] + m_pouvoir2[2] + m_pouvoir2[3];
                if(typeAny>=1)
                {
                    for(unsigned int i=0; i<m_pouvoir2.size(); i++)
                    {
                        if(m_pouvoir2[i]>=1)    //Regarde si le joueur a suffisament de point de Pouvoir quelconque
                        {
                            m_pouvoir2[i]--;
                            break;          //Execution de l'attaque
                        }
                    }
                }
                else                //Si le joueur n'a pas suffisament de point de Pouvoir quelconque
                {
                    m_pouvoir2[typeAttaque] +=2;
                    possibiliteAttaque = false;
                }
            }
            else
            {
                possibiliteAttaque = false;
            }
        }
    }
    return possibiliteAttaque;
}
///Realisation d'une Attaque
bool Jeu::attaquer(int nbAttaque, int nbJoueur)
{
    bool possibiliteAttaque = true;
    int degats = 0;
    int degatsJoueurs = 0;
    bool verif = false;
    if(nbJoueur==1)//Pour le joueur 1
    {
        if(m_dirigeant1->getNature()=="Dirigeant")//Vérification de la nature de l'attaquant
        {
            Pouvoir p = m_dirigeant1->getPouvoir();
            std::string type = p.getNom();
            if(type == "Militaire" && verif == false)   //Si le dirigeant est de type Militaire
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 0);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant1->attaquer(nbAttaque); //Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant2->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ2 -= degatsJoueurs;                    //Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Politique" && verif == false)//Si le dirigeant est de type Politique
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 1);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant1->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant2->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ2 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Economique" && verif == false)//Si le dirigeant est de type Economique
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 2);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant1->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant2->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ2 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Religieux" && verif == false)//Si le dirigeant est de type Religieu
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 3);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant1->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant2->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ2 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            else if(!verif)//Si le type du dirigeant n'existe pas
            {
                m_terrain.erreur("ERREUR de type dirigeant");
                possibiliteAttaque = false;
            }
        }
        else
        {
            m_terrain.erreur("ERREUR : Pas un dirigeant");
            possibiliteAttaque = false;
        }
    }                               //Pour le Joueur 2
    else
    {
        if(m_dirigeant2->getNature()=="Dirigeant")//Vérification de la nature de l'attaquant
        {
            Pouvoir p = m_dirigeant2->getPouvoir();
            std::string type = p.getNom();
            if(type == "Militaire" && verif == false)//Si le dirigeant est de type Militaire
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 0);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant2->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant1->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ1 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Politique" && verif == false)//Si le dirigeant est de type Politique
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 1);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant2->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant1->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ1 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Economique" && verif == false)//Si le dirigeant est de type Economique
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 2);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant2->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant1->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ1 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            if(type == "Religieux" && verif == false)//Si le dirigeant est de type Religieu
            {
                verif = true;
                possibiliteAttaque = coutAttaque(nbAttaque, nbJoueur, 3);//Calcul de la possibilité de l'attaque
                if(possibiliteAttaque)
                {
                    degats = m_dirigeant2->attaquer(nbAttaque);//Récupération des dégâts de l'attaque
                    degatsJoueurs = m_dirigeant1->subir(degats);//Le dirigeant adverse subit les dégats de l'attaque
                    m_pvJ1 -= degatsJoueurs;//Les dégâts résiduels sont infligés au Joueur adeverse
                }
            }
            else if(!verif)//Si le type du dirigeant n'existe pas
            {
                m_terrain.erreur("ERREUR de type dirigeant");
                possibiliteAttaque = false;
            }
        }
        else
        {
            m_terrain.erreur("ERREUR : Pas un dirigeant");
            possibiliteAttaque = false;
        }
    }
    return possibiliteAttaque;
}
///Deroulement d'un tour pour le joueur placée en paramètre
void Jeu::tour(int nbJoueur)
{
    m_terrain.setup();  //Affichage du plateau de jeu

    if(nbJoueur==1)//Pour le joueur 1
    {
        m_terrain.piocher(m_j1.getPseudo(), nbJoueur);  //Attente que le joueur pioche sa carte
        if(m_dirigeant1->getPV()<=0)//Si le joueur na pas/plus de dirigeant actif
        {
            Carte* pioche = new Carte();
            do
            {
                if(m_deck1.getDeck().empty())
                {
                    return;                 //Défaite si le deck est vide
                }
                pioche = m_deck1.piocher();
                if(pioche->getNature()!="Dirigeant")            //Pioche d'une carte jusqu'à avoir un dirigeant
                {
                    m_deck1.remettre(pioche);
                }
                else
                {
                    //std::cout<<"Le joueur "<<m_j1.getPseudo()<<" pioche et pose le dirigeant "<<pioche->getNom()<<" sur le terrain."<<std::endl;
                    m_dirigeant1 = pioche;
                }
            }while(pioche->getNature()!="Dirigeant");
            m_terrain.setDirigeant1(m_dirigeant1);  //Changement de dirigeant à l'écran
            m_terrain.setup();
        }
        else        //Si le dirigeant actif est en vie
        {
            m_terrain.setup();                      //Affichage du plateau de jeu
            Carte* pioche = new Carte();
            pioche = m_deck1.piocher();//Pioche d'une nouvelle carte
            Pouvoir p = pioche->getPouvoir();
            m_terrain.affCarte(900, 500, pioche);
            m_terrain.afficher();
            if(pioche->getNature()=="Energie")           //Ajout des Points de Pouvoir si la carte est une carte Energie
            {
                rest(1500);
                if(p.getNom()=="Militaire") m_pouvoir1[0] += 2;
                if(p.getNom()=="Politique") m_pouvoir1[1] += 2;
                if(p.getNom()=="Economique") m_pouvoir1[2] += 2;
                if(p.getNom()=="Religieux") m_pouvoir1[3] += 2;
                m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                m_terrain.setup();                      //Affichage du plateau de jeu
            }
            if(pioche->getNature()=="Dirigeant")        //Si la carte est un Dirigeant alors possibilité de scrifier l'actuel pour placer
            {                                           //le nouveau à la place ou de remettre le nouveau dans le deck
                m_terrain.afficher();
                int choix;
                std::vector<std::string> texteChoix;
                texteChoix.push_back("Souhaitez vous remplacer le dirigeant actuel par celui-ci ? ");
                texteChoix.push_back("1. Oui et tuer le dirigeant actuellement en place");
                texteChoix.push_back("2. Non et remetre le dirigeant pioche dans le deck");
                choix = m_terrain.texteConsole(texteChoix, 2);//Choix de l'action par l'utilisateur
                switch(choix)
                {
                case 1:
                    m_cimentiere1.push_back(m_dirigeant1);
                    m_dirigeant1 = pioche;
                    m_terrain.setDirigeant1(m_dirigeant1);
                    m_terrain.setup();//Affichage du plateau de jeu
                    break;
                case 2:
                    m_deck1.remettre(pioche);
                    m_terrain.setup();//Affichage du plateau de jeu
                    break;
                default:
                    m_terrain.erreur("Choix non valide");
                    break;
                }
            }
            if(pioche->getNature()=="Speciale") //Propose d'executer ou non la carte spéciale piochée
            {
                int choixSpe;/*
                do
                {
                    std::cout<<"Souhaitez vous jouer cette carte speciale ? "<<std::endl;
                    std::cout<<"1. Oui"<<std::endl;
                    std::cout<<"2. Non et la remetre dans le deck"<<std::endl;
                    std::cin>>choixSpe;
                    if(choixSpe<1 || choixSpe>2) std::cout<<"Choix non valide"<<std::endl;
                }while(choixSpe<1 || choixSpe>2);*/
                std::vector<std::string> texteChoix;
                texteChoix.push_back("Souhaitez vous jouer cette carte speciale ? ");
                texteChoix.push_back("1. Oui");
                texteChoix.push_back("2. Non et la remetre dans le deck");
                choixSpe = m_terrain.texteConsole(texteChoix, 2);//Choix de l'action par l'utilisateur
                switch(choixSpe)
                {
                case 1:
                    effetSpeciaux(nbJoueur, pioche->getNom());
                    m_terrain.setup();//Affichage du plateau de jeu
                    break;
                case 2:
                    m_deck1.remettre(pioche);   //Si non, la remettre dans le deck
                    m_terrain.setup();//Affichage du plateau de jeu
                    break;
                default:
                    m_terrain.erreur("Choix non valide");
                    break;
                }
            }
        }
        m_terrain.setDirigeant1(m_dirigeant1);
        m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
        m_terrain.afficher();   //Affichage du plateau de jeu
        if(m_dirigeant1->getPV()>0)
        {
            rest(1000);
            int choix2;
            bool attaque = true;
            do
            {
                m_terrain.setup(); //Affichage du plateau de jeu
                //Choix de l'action à executer avec le Dirigeant actif
                attaque = true;
                std::vector<std::string> texteChoix;
                std::vector<std::string> texteMsg;
                texteChoix.push_back("Que souhaitez-vous faire avec votre dirigeant actif ? ");
                texteChoix.push_back("1. Attaquer en utilisant la premiere attaque (1 point d'energie)");
                texteChoix.push_back("2. Attaquer en utilisant la deuxieme attaque (3 points d'energie)");
                texteChoix.push_back("3. Ne rien faire");
                choix2 = m_terrain.texteConsole(texteChoix, 3);

                switch(choix2)
                {
                case 1:
                    attaque = attaquer(1, nbJoueur);
                    if(!attaque)
                    {
                        m_terrain.setup();
                        texteMsg.push_back("Vous n'avez pas assez de points de pouvoir pour effectuer cette attaque.");
                        m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                        m_terrain.texteConsole(texteMsg, 0);
                        m_terrain.afficher();//Affichage du plateau de jeu
                        rest(800);
                        //std::cout<<"ERREUR : l'attaque n'a pas ete execute !"<<std::endl;
                    }
                    break;
                case 2:
                    attaque = attaquer(2, nbJoueur);
                    if(!attaque)
                    {
                        m_terrain.setup();
                        texteMsg.push_back("Vous n'avez pas assez de points de pouvoir pour effectuer cette attaque.");
                        m_terrain.texteConsole(texteMsg, 0);
                        m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                        m_terrain.afficher();//Affichage du plateau de jeu
                        rest(800);
                        //std::cout<<"ERREUR : l'attaque n'a pas ete execute !"<<std::endl;
                    }
                    break;
                case 3:
                    m_terrain.setup();
                    texteMsg.push_back("Vous avez choisi de ne rien faire.");
                    m_terrain.texteConsole(texteMsg, 0);
                    m_terrain.afficher();//Affichage du plateau de jeu
                    rest(700);
                    break;
                default:
                    texteMsg.push_back("Choix non valide");
                    m_terrain.texteConsole(texteMsg, 0);
                    break;
                }
            }while(choix2<1 || choix2>3 || !attaque);

            if(m_francisque)//Remise du multiplicateur de la carte spéciale Francisque à la normale si elle était active ce tour
            {
                m_francisque = false;
                m_dirigeant1->setMultiplicateur(-3);
            }
        }
        if(m_famine>0)  //Décrémentation du compteur de la carte spéciale Famine si elle est active
        {
            std::vector<std::string> texteMsg;
            rest(200);
            texteMsg.push_back("Le dirigeant " + m_dirigeant1->getNom() + " subit un point de degat de la famine !");
            m_terrain.texteConsole(texteMsg, 0);
            m_dirigeant1->subir(1);
            m_famine --;
            rest(700);
        }
        m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
        m_terrain.setPv(m_j1.getPseudo(), m_j2.getPseudo(), m_pvJ1, m_pvJ2);
        m_terrain.setup();//Affichage du plateau de jeu
    }
    if(nbJoueur==2)//Pour le joueur 2
    {
        m_terrain.piocher(m_j2.getPseudo(), nbJoueur);//Attente que le joueur pioche une carte
        if(m_pvJ2>0)//Si le joueur na pas/plus de dirigeant actif
        {
                if(m_dirigeant2->getPV()<=0)
            {
                Carte* pioche = new Carte();
                do
                {
                    if(m_deck2.getDeck().empty())
                    {
                        return;//Défaite si le deck est vide
                    }
                    pioche = m_deck2.piocher();
                    if(pioche->getNature()!="Dirigeant")
                    {
                        m_deck2.remettre(pioche);//Pioche d'une carte jusqu'à avoir un dirigeant
                    }
                    else
                    {
                        //std::cout<<"Le joueur "<<m_j2.getPseudo()<<" pioche et pose le dirigeant "<<pioche->getNom()<<" sur le terrain."<<std::endl;
                        m_dirigeant2 = pioche;
                    }
                }while(pioche->getNature()!="Dirigeant");
                m_terrain.setDirigeant2(m_dirigeant2);
                m_terrain.setup();//Affichage du plateau de jeu
            }
            else//Si le dirigeant actif est en vie
            {
                m_terrain.setup();//Affichage du plateau de jeu
                Carte* pioche = new Carte();
                pioche = m_deck2.piocher();//Pioche d'une nouvelle carte
                Pouvoir p = pioche->getPouvoir();
                m_terrain.affCarte(300, -10, pioche);
                m_terrain.afficher();
                if(pioche->getNature()=="Energie")//Ajout des Points de Pouvoir si la carte est une carte Energie
                {
                    rest(1500);
                    if(p.getNom()=="Militaire") m_pouvoir2[0] += 2;
                    if(p.getNom()=="Politique") m_pouvoir2[1] += 2;
                    if(p.getNom()=="Economique") m_pouvoir2[2] += 2;
                    if(p.getNom()=="Religieux") m_pouvoir2[3] += 2;
                    m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                    m_terrain.setup();//Affichage du plateau de jeu
                }
                if(pioche->getNature()=="Dirigeant")//Si la carte est un Dirigeant alors possibilité de scrifier l'actuel pour placer
                {                                   //le nouveau à la place ou de remettre le nouveau dans le deck
                    m_terrain.afficher();
                    int choix;/*
                    do
                    {
                        std::cout<<"Souhaitez vous remplacer le dirigeant actuel par celui-ci ? "<<std::endl;
                        std::cout<<"1. Oui et tuer le dirigeant actuelement en place"<<std::endl;
                        std::cout<<"2. Non et remetre le dirigeant pioche dans le deck"<<std::endl;
                        std::cin>>choix;
                        if(choix<1 || choix>2) std::cout<<"Choix non valide"<<std::endl;
                    }while(choix<1 || choix>2);*/
                    std::vector<std::string> texteChoix;
                    texteChoix.push_back("Souhaitez vous remplacer le dirigeant actuel par celui-ci ? ");
                    texteChoix.push_back("1. Oui et tuer le dirigeant actuellement en place");
                    texteChoix.push_back("2. Non et remetre le dirigeant pioche dans le deck");
                    choix = m_terrain.texteConsole(texteChoix, 2);//Choix de l'action par l'utilisateur
                    switch(choix)
                    {
                    case 1:
                        m_cimentiere2.push_back(m_dirigeant1);
                        m_dirigeant2 = pioche;
                        m_terrain.setDirigeant2(m_dirigeant2);
                        m_terrain.setup();//Affichage du plateau de jeu
                        break;
                    case 2:
                        m_deck2.remettre(pioche);
                        m_terrain.setup();//Affichage du plateau de jeu
                        break;
                    default:
                        m_terrain.erreur("Choix non valide");
                        break;
                    }
                }
                if(pioche->getNature()=="Speciale")//Propose d'executer ou non la carte spéciale piochée
                {
                    int choixSpe;
                    std::vector<std::string> texteChoix;
                    texteChoix.push_back("Souhaitez vous jouer cette carte speciale ? ");
                    texteChoix.push_back("1. Oui");
                    texteChoix.push_back("2. Non et la remetre dans le deck");
                    choixSpe = m_terrain.texteConsole(texteChoix, 2);//Choix de l'action par l'utilisateur
                    switch(choixSpe)
                    {
                    case 1:
                        effetSpeciaux(nbJoueur, pioche->getNom());
                        m_terrain.setup();//Affichage du plateau de jeu
                        break;
                    case 2:
                        m_deck2.remettre(pioche);//Si non, la remettre dans le deck
                        m_terrain.setup();//Affichage du plateau de jeu
                        break;
                    default:
                        m_terrain.erreur("Choix non valide");
                        break;
                    }
                }
            }
            m_terrain.setDirigeant2(m_dirigeant2);
            m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
            m_terrain.afficher();//Affichage du plateau de jeu
            if(m_dirigeant2->getPV()>0)//Choix de l'action à executer avec le Dirigeant actif
            {
                rest(1000);
                int choix2;
                bool attaque = true;
                do
                {
                    m_terrain.setup();
                    attaque = true;
                    std::vector<std::string> texteChoix;
                    std::vector<std::string> texteMsg;
                    texteChoix.push_back("Que souhaitez-vous faire avec votre dirigeant actif ? ");
                    texteChoix.push_back("1. Attaquer en utilisant la premiere attaque (1 point d'energie)");
                    texteChoix.push_back("2. Attaquer en utilisant la deuxieme attaque (3 points d'energie)");
                    texteChoix.push_back("3. Ne rien faire");
                    choix2 = m_terrain.texteConsole(texteChoix, 3);//Choix de l'action par l'utilisateur
                    switch(choix2)
                    {
                    case 1:
                        attaque = attaquer(1, nbJoueur);
                        if(!attaque)
                        {
                            m_terrain.setup();
                            texteMsg.push_back("Vous n'avez pas assez de points de pouvoir pour effectuer cette attaque.");
                            m_terrain.texteConsole(texteMsg, 0);
                            m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                            m_terrain.afficher();//Affichage du plateau de jeu
                            rest(800);
                            //std::cout<<"ERREUR : l'attaque n'a pas ete execute !"<<std::endl;
                        }
                        break;
                    case 2:
                        attaque = attaquer(2, nbJoueur);
                        if(!attaque)
                        {
                            m_terrain.setup();
                            texteMsg.push_back("Vous n'avez pas assez de points de pouvoir pour effectuer cette attaque.");
                            m_terrain.texteConsole(texteMsg, 0);
                            m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
                            m_terrain.afficher();//Affichage du plateau de jeu
                            rest(800);
                            //std::cout<<"ERREUR : l'attaque n'a pas ete execute !"<<std::endl;
                        }
                        break;
                    case 3:
                        m_terrain.setup();
                        texteMsg.push_back("Vous avez choisi de ne rien faire.");
                        m_terrain.texteConsole(texteMsg, 0);
                        m_terrain.afficher();//Affichage du plateau de jeu
                        rest(700);
                        break;
                    default:
                        texteMsg.push_back("Choix non valide");
                        m_terrain.texteConsole(texteMsg, 0);
                        break;
                    }
                }while(choix2<1 || choix2>3 || !attaque);
                m_terrain.setup();//Affichage du plateau de jeu
                if(m_francisque)
                {//Remise du multiplicateur de la carte spéciale Francisque à la normale si elle était active ce tour
                    m_francisque = false;
                    m_dirigeant2->setMultiplicateur(-3);
                }
            }
            if(m_famine>0)//Décrémentation du compteur de la carte spéciale Famine si elle est active
            {
                std::vector<std::string> texteMsg;
                //std::cout<<"Le dirigeant "<<m_dirigeant2->getNom()<<" subit un point de degat de la famine !"<<std::endl;
                texteMsg.push_back("Le dirigeant " + m_dirigeant2->getNom() + " subit un point de degat de la famine !");
                m_terrain.texteConsole(texteMsg, 0);
                m_dirigeant2->subir(1);
                m_famine--;
                rest(700);
            }
            m_terrain.setPouvoirs(m_pouvoir1, m_pouvoir2);
            m_terrain.setPv(m_j1.getPseudo(), m_j2.getPseudo(), m_pvJ1, m_pvJ2);
            m_terrain.setup();//Affichage du plateau de jeu
        }
    }
}
///Déroulement d'une partie
void Jeu::deroulementJeu()
{
    bool fin = false;
    int gagnant;//Numéro du joueur vainqueur
    do
    {
        if(m_pvJ1>0)//Vérification si le joueur est toujours en vie
        {
            if(m_deck1.getDeck().empty())
            {//Défaite si le deck est vide
                m_terrain.emphase("Le Joueur " + m_j1.getPseudo() + " n'a plus de carte dans son deck.", "Il perd la partie !");
                m_vainqueur = m_j2;
                gagnant = 2;
                rest(700);
                fin = true;
            }
            else
            {
                m_terrain.emphase("C'est a votre tour de Jouer !", m_j1.getPseudo());
                rest(400);
                tour(1);//Lancement du tour du joueur 1
                if(m_pvJ2<=0)//Test de fin de partie
                {
                    m_vainqueur = m_j1;
                    gagnant = 1;
                    fin = true;
                }
            }
        }
        else
        {
            m_terrain.emphase("Victoire !", m_j1.getPseudo() + " a gagne !");
            m_vainqueur = m_j1;
            gagnant = 1;
            fin = true;
            rest(700);
            break;
        }
        if(!fin)//Vérification si la partie doit s'arrêter dès maintenant
        {
            if(m_pvJ2>0)//Vérification si le joueur est toujours en vie
            {
                if(m_deck2.getDeck().empty())
                {//Défaite si le deck est vide
                    m_terrain.emphase("Le Joueur " + m_j2.getPseudo() + " n'a plus de carte dans son deck.", "Il perd la partie !");
                    m_vainqueur = m_j1;
                    gagnant = 1;
                    rest(700);
                    fin = true;
                }
                else
                {
                    m_terrain.emphase("C'est a votre tour de Jouer !", m_j2.getPseudo());
                    rest(400);
                    tour(2);//Lancement du tour du joueur 2
                    if(m_pvJ1<=0)//Test de fin de partie
                    {
                        m_vainqueur = m_j2;
                        gagnant = 2;
                        fin = true;
                    }
                }
            }
            else
            {
                m_terrain.emphase("Victoire !", m_j2.getPseudo() + " a gagne !");
                m_vainqueur = m_j2;
                gagnant = 2;
                fin = true;
                rest(700);
                break;
            }
        }

    }while(!fin);
    enjeu(gagnant);//Ajout de l'enjeu au deck et à la collection du vainqueur
    m_terrain.endgame(m_enjeu1, m_enjeu2, m_vainqueur.getPseudo());//Affichage des cartes remportées par le vainqueur
    rest(200);
    m_vainqueur.addMoney(1);//Ajout d'un Coin à la bourse du vainqueur qui peut les dépenser à la boutique pour acheter de nouvelles cartes
    m_terrain.emphase(m_vainqueur.getPseudo() + " gagne un Coin", "Les coins permettent d'acheter des cartes a la boutique");
    Scores s(m_terrain);
    s.ajoutVictoire(m_vainqueur.getPseudo());//Ajout d'une victoire au tableau des victoires pour le vainqueur
}
