#include "Terrain.h"
#include "time.h"
//#include <logg.h>
#include <iostream>

Terrain::Terrain(){}

Terrain::Terrain(std::string init)///Initialisation du mode graphique avec tout ses prérequis
{
    ///Initialisation
    m_pouvoir1 = {0,0,0,0};
    m_pouvoir2 = {0,0,0,0};
    m_textEnergie.push_back("Pouvoirs Militaires : ");
    m_textEnergie.push_back("Pouvoirs Politiques : ");
    m_textEnergie.push_back("Pouvoirs Economiques:");
    m_textEnergie.push_back("Pouvoirs Religieux : ");
    m_dirigeant1 = new Dirigeant();
    m_dirigeant2 = new Dirigeant();
    m_pvJ1 = "";
    m_pvJ2 = "";

    /// Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();
    register_png_file_type();
    jpgalleg_init();
    set_color_depth(desktop_color_depth());
    //if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,1600,900,0,0)!=0)
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1600,900,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    ///chargement des images
    m_pioche = load_bitmap_check("img/dos.jpg");
    m_background = load_bitmap_check("img/Fond.jpg");
    m_energie = load_bitmap_check("img/Parchemin.bmp");
    m_frameDir = load_bitmap_check("img/Dirigeant.bmp");
    m_console = load_bitmap_check("img/Console.bmp");
    m_pancarte = load_bitmap_check("img/pancarte.bmp");

    ///Lancement de la musique d'arrière plan
    m_musique = load_midi("Musique.mid");
    play_midi(m_musique, true);

    // Allocation dynamique d'une structure BITMAP de 1600 par 900
    m_plato=create_bitmap(1600,900);
    blit(m_background,m_plato,0,0,0,0,SCREEN_W,SCREEN_H);
}
Terrain::~Terrain(){}

void Terrain::setup()///affichage des éléments de base d'une partie
{
    setPouvoirs(m_pouvoir1, m_pouvoir2);
    //background & pioches
    blit(m_background,m_plato,0,0,0,0,SCREEN_W,SCREEN_H);
    masked_blit(m_pioche,m_plato,0,0,1360,535,SCREEN_W,SCREEN_H);
    masked_blit(m_pioche,m_plato,0,0,10,10,SCREEN_W,SCREEN_H);
    blit(m_console,m_plato,0,0,0,625,SCREEN_W,SCREEN_H);
    masked_blit(m_pancarte,m_plato,0,0,SCREEN_W-300,SCREEN_H/2-200,SCREEN_W,SCREEN_H);

    FONT *Font1 = load_font("Fonts/Font1.pcx",NULL,NULL);
    FONT *old = load_font("Fonts/Old.pcx",NULL,NULL);

    //Energies
    int i = 0, j = 455, k = 33;

    masked_blit(m_energie,m_plato,20,0,0,j-20,SCREEN_W,SCREEN_H);
    for(const auto& elem:m_textEnergie)
    {
        std::string nb = std::to_string(m_pouvoir1[i]);
        textout_ex(m_plato, Font1,elem.c_str(), k, j, makecol(160,108,61),-1);
        textout_ex(m_plato, Font1,nb.c_str(), k+265, j, makecol(0,180,255),-1);
        j+=30; i++;
    }
    i = 0, j = 15, k = 1280;
    masked_blit(m_energie,m_plato,0,0,1220,0,SCREEN_W,SCREEN_H);
    for(const auto& chose:m_textEnergie)
    {
        std::string nb = std::to_string(m_pouvoir2[i]);
        textout_ex(m_plato, Font1,chose.c_str(), k, j, makecol(160,108,61),-1);
        textout_ex(m_plato, Font1,nb.c_str(), k+265, j, makecol(0,180,255),-1);
        j+=30; i++;
    }

    //PV Joueurs
    textout_right_ex(m_plato, old,m_pvJ1.c_str(), SCREEN_W-42, SCREEN_H/2-50, makecol(220,220,220),-1);
    textout_right_ex(m_plato, old,m_pvJ2.c_str(), SCREEN_W-42, SCREEN_H/2-15, makecol(220,220,220),-1);

    //Dirigeants
    affCarte(500,460, m_dirigeant1);
    affCarte(700,10, m_dirigeant2);
    afficher();
}

BITMAP * Terrain::load_bitmap_check(std::string nomImage)///Méthode du chargement d'une image en vérifiant son existance, obtenue sur le site de M. Fercoq
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage.c_str(),NULL);
    if (!bmp)
    {
        std::string msg = "pas pu trouver "+nomImage;
        allegro_message(msg.c_str());
        exit(EXIT_FAILURE);
    }
    return bmp;
}

void Terrain::affCarte(int coordX, int coordY, Carte* carte)//Affichage d'une carte donnée à des coordonées x et y données sur le plateau de jeu
{
    //Chargement des polices de texte
    FONT *Name = load_font("Fonts/Nom.pcx",NULL,NULL);
    FONT *Font1 = load_font("Fonts/Font1.pcx",NULL,NULL);
    FONT *descriptif = load_font("Fonts/descriptif.pcx",NULL,NULL);
    FONT *font = Font1;
    int w = 40, ligne = 0, m=w;

    //affichage de la carte vide
    masked_blit(m_frameDir,m_plato,0,0,coordX,coordY,SCREEN_W,SCREEN_H);

    //couleurs et espacement de texte en fonction du type de carte
    int c=makecol(255,200,0);
    if(carte->getNature()=="Dirigeant") {c=makecol(255,200,0); font = descriptif; m = 30;}
    if(carte->getNature()=="Energie") {c=makecol(40,255,20);  }
    if(carte->getNature()=="Speciale") {c=makecol(255,50,50);      }
    line(m_plato,coordX+9,coordY+75,coordX+290,coordY+75,c);
    textout_centre_ex(m_plato, Name,carte->getNom().c_str(), coordX+150, coordY+30, c,-1);
    w = m;
    int i = coordX + 150, j = coordY+75;
    for(const auto& elem:carte->graphisme())
    {
        if(carte->getNature()=="Dirigeant" && ligne==4)
        {
            w=-30;
            j+=w;
        }
        if(carte->getNature()=="Speciale" && ligne == 1)//Lorsque sur la ligne du texte descriptif de la carte
        {
            w=20;
            int taille = elem.size();
            std::vector<std::string> texte = text(elem);//couper le texte une première fois en deux
            taille-=texte[0].size();
            textout_centre_ex(m_plato, descriptif,texte[0].c_str(), i, j, c,-1);
            int n = 0;
            do                                          //Le refaire autant de fois que nécéssaire
            {
                if(taille>=27 || texte[texte.size()-1].size()>30)
                {
                    texte = text(texte[1]);
                    taille-=texte[1].size();
                    n=0;
                    textout_centre_ex(m_plato, descriptif,texte[n].c_str(), i, j+w, c,-1);
                    j+=w;
                }
                else
                {
                    textout_centre_ex(m_plato, descriptif,texte[n].c_str(), i, j, c,-1);
                }
                j+=w; n++;
            }while(n<(int) texte.size());
        }
        else if(carte->getNature()=="Energie" && ligne == 3)//Lorsque sur la ligne de la légende de la carte
        {
            int taille = elem.size();
            std::vector<std::string> texte = text(elem);//couper le texte une première fois en deux
            taille-=texte[1].size();
            w=12;
            textout_centre_ex(m_plato, descriptif,texte[0].c_str(), i, j, c,-1);
            int n = 0;
            do                                          //Le refaire autant de fois que nécéssaire
            {
                if(taille>=27 || texte[texte.size()-1].size()>30)
                {
                    texte = text(texte[1]);
                    taille-=texte[1].size();
                    n=0;
                    textout_centre_ex(m_plato, descriptif,texte[n].c_str(), i, j+w+5, c,-1);
                    j+=2*w;
                }
                else
                {
                    textout_centre_ex(m_plato, descriptif,texte[n].c_str(), i, j, c,-1);
                }
                j+=w; n++;
            }while(n<(int) texte.size());
        }
        else
        {
            textout_centre_ex(m_plato, font,elem.c_str(), i, j, c,-1);
            w = m;
            j+=w;
        }
        ligne++;
    }
    line(m_plato,coordX+9,coordY+350,coordX+290,coordY+350,c);
    textout_centre_ex(m_plato, Font1,carte->getNature().c_str(), coordX+150, coordY+345, c,-1);//Affichage de la nature de la carte
}

std::vector<std::string> Terrain::text(std::string str)/// http://www.cplusplus.com/reference/string/string/substr/
{                                                      ///Méthode permettant de séparer une chaîne de charactères en 2 aux endroits comprenant un #, obtenue sur cppplusplus.com
    std::size_t pos = str.find("# ");      // position de "# " dans str, soit l'emplacement ou l'on coupe en deux notre chaîne de charactères
    std::string str1 = str.substr(0, pos);
    std::string str2 = str.substr(pos+1);
    std::vector<std::string> vec = {str1, str2};
    return vec;
}

void Terrain::setDirigeant1(Carte* dir1)///setter pour le dirigeant actif du joueur 1
{
    m_dirigeant1 = dir1;
}
void Terrain::setDirigeant2(Carte* dir2)///setter pour le dirigeant actif du joueur 2
{
    m_dirigeant2 = dir2;
}
void Terrain::setPouvoirs(std::vector<int> pouvoir1, std::vector<int> pouvoir2)///setter pour les stockages d'énergies/pouvoirs de chaque joueur
{
    m_pouvoir1 = pouvoir1;
    m_pouvoir2 = pouvoir2;
    //Affichage des jauges
    afficher();
}

void Terrain::setPv(std::string pseudo1, std::string pseudo2, int pv1, int pv2)///setter pour les pv de chaque joueur
{
    m_pvJ1 = pseudo1 + ": " + std::to_string(pv1) + "PV";
    m_pvJ2 = pseudo2 + ": " + std::to_string(pv2) + "PV";
}

void Terrain::afficher()///affichages des éléments du buffer
{                       ///obtenue sur le site de M. Fercoq
    int x,y;
    x=(SCREEN_W-m_plato->w)/2;
    y=(SCREEN_H-m_plato->h)/2;

    install_mouse();
    show_mouse(screen);

    // Affichage de la Bitmap sur l'écran à ces coordonnées
    blit(m_plato, screen, 0,0, x, y, m_plato->w, m_plato->h);
}

int Terrain::texteConsole(std::vector<std::string> texte, int nbChoix)///écriture d'un texte et choix par l'utilisateur à la souris de quelque chose dans la console de dialogue
{

    // Pour disposer des caractères ascii étendus (avec accents)
    set_uformat(U_ASCII);
    if(nbChoix>0)
    {
        rect(m_plato, 30, 720, 450, 745, makecol(160,108,61));
        rect(m_plato, 30, 746, 450, 770, makecol(160,108,61));
        if(nbChoix>2) rect(m_plato, 30, 771, 450, 795, makecol(160,108,61));
    }

    //affichage du texte
    FONT *console = load_font("Fonts/console.pcx",NULL,NULL);
    int j=700;
    for(const auto& elem:texte)
    {
        textout_ex(m_plato, console,elem.c_str(), 37, j, makecol(0,0,0),-1);
        j+=25;
    }

    // pour disposer de la souris
    install_mouse();

    // pour voir le pointeur de la souris
    show_mouse(m_plato);

    int choix = 0;

    bool fin = false;
    afficher();
    if(nbChoix>0)               //si l'utilisateur a un choix à faire
    {
        while (!fin)            //attente de la sélection par l'utilisateur
        {
            if ( mouse_b&1 && mouse_y>=720 && mouse_x<=450 &&mouse_y<=745)
            {
                choix = 1;      //premier choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_y>=746 && mouse_x<=450 &&mouse_y<=770)
            {
                choix = 2;      //deuxième choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_y>=771 && mouse_x<=450 &&mouse_y<=795 && nbChoix>2)
            {
                choix = 3;      //troisième choix
                fin = true;
            }
        }
    }
    return choix;
}

void Terrain::emphase(std::string titre, std::string sousTitre)
{                       ///Message accentué avec une première chose écrite en gros et une seconde en un peu plus petit en dessous
    FONT *MiddleTitle = load_font("Fonts/MiddleTitle.pcx",NULL,NULL);
    FONT *SubTitle = load_font("Fonts/SubTitle.pcx",NULL,NULL);

    // Texte centré
    textout_centre_ex(m_plato, MiddleTitle,titre.c_str(), SCREEN_W/2,SCREEN_H/2-100, makecol(255,200,0),-1);
    textout_centre_ex(m_plato, SubTitle,sousTitre.c_str(), SCREEN_W/2,SCREEN_H/2-20, makecol(0,170,250),-1);

    afficher();
}

void Terrain::piocher(std::string pseudo, int nbJoueur) ///Demande à un des deux joueurs de cliquer sur son deck pour mimer un piochage de carte
{
    emphase("Piochez une Carte", pseudo);
    bool fin = false;
    while(!fin)
    {
        if(nbJoueur==1)
        {
            if ( mouse_b&1 && mouse_x>=1360 && mouse_y>=535)
            fin=1;
        }
        if(nbJoueur==2)
        {
            if ( mouse_b&1 && mouse_x<=250 && mouse_y<=380)
            fin=1;
        }
    }
}

void Terrain::endgame(Carte* enjeu1, Carte* enjeu2, std::string pseudo)///Affiche les cartes tirées comme enjeu gagnées par le vainqueur
{
    // Effacer contenu éventuel qui traine en mémoire
    // -> tous les pixels sont mis à noir
    clear_bitmap(m_plato);
    blit(m_background,m_plato,0,0,0,0,SCREEN_W,SCREEN_H);
    affCarte(SCREEN_W/2-450, SCREEN_H/2, enjeu1);
    affCarte(SCREEN_W/2+200, SCREEN_H/2, enjeu2);
    emphase("Victoire !", pseudo+" remporte les cartes suivantes");
    rest(4000);

}

void Terrain::partie(Carte* dirigeant1, Carte* dirigeant2)//Initialisation de l'affichage pour une partie
{
    setDirigeant1(dirigeant1);
    setDirigeant1(dirigeant2);

    // Effacer contenu éventuel qui traine en mémoire
    // -> tous les pixels sont mis à noir
    clear_bitmap(m_plato);
    setPouvoirs(m_pouvoir1, m_pouvoir2);

    //background & pioches
    blit(m_background,m_plato,0,0,0,0,SCREEN_W,SCREEN_H);
    masked_blit(m_pioche,m_plato,0,0,1360,535,SCREEN_W,SCREEN_H);
    masked_blit(m_pioche,m_plato,0,0,10,10,SCREEN_W,SCREEN_H);
    blit(m_console,m_plato,0,0,0,625,SCREEN_W,SCREEN_H);
    masked_blit(m_pancarte,m_plato,0,0,SCREEN_W-300,SCREEN_H/2-200,SCREEN_W,SCREEN_H);
    afficher();
}

int Terrain::menu(std::string titre, std::vector<std::string> propositions, int nbChoix)///Menu divers avec choix paramétrables, attendant un clic de l'utilisateur sur une des options proposées
{
    //Polices utilisées
    FONT *MiddleTitle = load_font("Fonts/MiddleTitle.pcx",NULL,NULL);
    FONT *SubTitle = load_font("Fonts/SubTitle.pcx",NULL,NULL);

    //image de fond
    BITMAP* menu = load_bitmap_check("img/Menu.bmp");
    masked_blit(menu,m_plato,0,0,SCREEN_W/2-360,SCREEN_H/10-72,SCREEN_W,SCREEN_H);

    //Texte centré
    textout_centre_ex(m_plato, MiddleTitle,titre.c_str(), SCREEN_W/2,SCREEN_H/4, makecol(213,70,40),-1);
    int j=100;
    for(const auto& elem: propositions)
    {
        textout_centre_ex(m_plato, SubTitle,elem.c_str(), SCREEN_W/2,SCREEN_H/4+j, makecol(160,108,61),-1);
        j+=75;
    }

    // pour disposer de la souris
    install_mouse();

    // pour voir le pointeur de la souris
    show_mouse(m_plato);

    int choix = 0;

    bool fin = false;
    afficher();
    if(nbChoix>0)//Si il y a un chois à faire
    {
        while (!fin)    //Attente que l'utilisateur fasse son choix
        {
            if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+90 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+160)
            {
                choix = 1;//Premier choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+165 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+235)
            {
                choix = 2;//Deuxième choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+245 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+315 && nbChoix>2)
            {
                choix = 3;//Troisième choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+320 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+395 && nbChoix>3)
            {
                choix = 4;//Quatrième choix
                fin = true;
            }
            if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+400 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+475 && nbChoix>4)
            {
                choix = 5;//Cinquième choix
                fin = true;
            }
        }
    }
    return choix;
}

std::string Terrain::saisie(std::string titre, std::string texte)///saisie similaire à un "std::getline(std::cin, variable)" de l'utilisateur, pour allegro
{                                                                ///obtenu en partie sur le site de M. Fercoq
    std::string saisie;
    int poscarac=0; //position du charactère pour son affichage
    bool fin = false;
    int touche;
    //Polices utilisées
    FONT *MiddleTitle = load_font("Fonts/MiddleTitle.pcx",NULL,NULL);
    FONT *SubTitle = load_font("Fonts/SubTitle.pcx",NULL,NULL);
    //Ce que l'on demande à l'utilisateur
    textout_centre_ex(m_plato, MiddleTitle,titre.c_str(), SCREEN_W/2,SCREEN_H/4, makecol(255,200,0),-1);
    textout_centre_ex(m_plato, SubTitle,texte.c_str(), SCREEN_W/2,SCREEN_H/4+80, makecol(160,108,61),-1);
    afficher();
    set_keyboard_rate(500,200); //pour éviter qu'un appui de touche fasse apparaître plus de charactères que désiré
    rest(50);
    char carac;                 //Charactère saisi
    while (!fin)
    {

        // keypressed() : détection de touche appuyée
        if (keypressed())
        {
            effacer();
            textout_centre_ex(m_plato, MiddleTitle,titre.c_str(), SCREEN_W/2,SCREEN_H/4, makecol(255,200,0),-1);
            textout_centre_ex(m_plato, SubTitle,texte.c_str(), SCREEN_W/2,SCREEN_H/4+80, makecol(160,108,61),-1);
            // récupérer la touche avec readkey()
            touche=readkey();
            carac = (char) touche;
            if(carac=='\r'||key[KEY_BACKSPACE]) //si l'utilisateur appuie sur un charactère non supporté ou veut effacer le dernier en appuyant sur la touche [BACKSPACE]
            {
                std::size_t pos = saisie.size(); //On enlève le dernier charactère de la saisie
                saisie = saisie.substr(0, pos-1);
            }
            else
            {
                // a partir de l'info de touche on obtient le caractère en castant en char
                saisie +=(char) touche;
            }
            textout_centre_ex(m_plato, SubTitle,saisie.c_str(), SCREEN_W/2,SCREEN_H/2, makecol(160,108,61),-1);
            poscarac=poscarac+20;
            afficher();

        }
        if (key[KEY_ENTER]) //si l'utilisateur confirme sa saisie avec Entrée
                fin=true;
    }
    effacer();
    return saisie;
}

void Terrain::effacer()///effacer tous les éléments actuellement en buffer
{                      ///Obtenu sur le site de M. Fercoq
    // Effacer contenu éventuel qui traine en mémoire
    // -> tous les pixels sont mis à noir
    clear_bitmap(m_plato);
    blit(m_background,m_plato,0,0,0,0,SCREEN_W,SCREEN_H);
    afficher();
}

void Terrain::erreur(std::string msg)///Message d'erreur en rouge au bas de l'écran
{
    //Police
    FONT *SubTitle = load_font("Fonts/SubTitle.pcx",NULL,NULL);
    //Message
    textout_centre_ex(m_plato, SubTitle,msg.c_str(), SCREEN_W/2,SCREEN_H/4*3, makecol(255,50,50),-1);
    afficher();
    rest(1500);
}

int Terrain::menuPrincipal()///Menu principal du jeu, attendant un clic de l'utilisateur sur une des options proposées
{
    effacer();
    //Chargement des images
    BITMAP* baniere = load_bitmap_check("img/Baniere.bmp");
    BITMAP* arrow1 = load_bitmap_check("img/arrow1.bmp");
    BITMAP* arrow2 = load_bitmap_check("img/arrow2.bmp");
    masked_blit(baniere,m_plato,0,0,SCREEN_W/2-566,0,SCREEN_W,SCREEN_H);

    //Chargement des polices
    FONT *MainTitle = load_font("Fonts/MainTitle.pcx",NULL,NULL);
    FONT *MiddleTitle = load_font("Fonts/MiddleTitle.pcx",NULL,NULL);

    //Affichage du titre du jeu
    textout_centre_ex(m_plato, MainTitle,"Batailles        d'Etats", SCREEN_W/2,SCREEN_H/4-75, makecol(255,200,0),-1);
    textout_centre_ex(m_plato, MainTitle," & coups", SCREEN_W/2+7,SCREEN_H/4-90, makecol(255,200,0),-1);

    std::vector<std::string> propositions;//Ajout des choix à afficher
    propositions.push_back("Jouer");
    propositions.push_back("Regles");
    propositions.push_back("Creer mon Deck");
    propositions.push_back("Boutique");
    propositions.push_back("Credits");
    propositions.push_back("Extras");
    propositions.push_back("Quitter");
    int j=50, choix;
    for(const auto& elem: propositions)//Affichage des choix
    {
        textout_centre_ex(m_plato, MiddleTitle,elem.c_str(), SCREEN_W/2,SCREEN_H/4+j, makecol(255,200,0),-1);
        j+=85;
    }
    bool fin = false;
    afficher();
    while (!fin)//Attente que l'utilisateur fasse son choix
    {

        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+50 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+140)
        {
            choix = 1;//Lancer le jeu
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+60,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+60,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+145 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+225)
        {
            choix = 2;//Affichge des règles
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+155,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+155,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+230 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+310)
        {
            choix = 3;//Sous-menus de création de deck
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+240,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+240,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+315 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+395)
        {
            choix = 4;//ouverture de la boutique
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+325,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+325,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+400 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+480)
        {
            choix = 5;//Affichage des crédits
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+410,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+410,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+485 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+565)
        {
            choix = 6;//Sous-menu des extensions
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+495,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+495,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+570 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+650)
        {
            choix = 7;//Quitter
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+580,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+580,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
    }
    return choix;
}

int Terrain::menuExtras()///Menu des extensions du jeu, attendant un clic de l'utilisateur sur une des options proposées
{
    effacer();
    //Chargement des images
    BITMAP* baniere = load_bitmap_check("img/Baniere.bmp");
    BITMAP* arrow1 = load_bitmap_check("img/arrow1.bmp");
    BITMAP* arrow2 = load_bitmap_check("img/arrow2.bmp");
    masked_blit(baniere,m_plato,0,0,SCREEN_W/2-566,0,SCREEN_W,SCREEN_H);

    //Chargement des polices
    FONT *MainTitle = load_font("Fonts/MainTitle.pcx",NULL,NULL);
    FONT *MiddleTitle = load_font("Fonts/MiddleTitle.pcx",NULL,NULL);

    //Affichage du titre du jeu
    textout_centre_ex(m_plato, MainTitle,"Batailles        d'Etats", SCREEN_W/2,SCREEN_H/4-75, makecol(255,200,0),-1);
    textout_centre_ex(m_plato, MainTitle," & coups", SCREEN_W/2+7,SCREEN_H/4-90, makecol(255,200,0),-1);

    std::vector<std::string> propositions;//Ajout des choix à afficher
    propositions.push_back("Creer des cartes");
    propositions.push_back("Meilleurs joueurs");
    propositions.push_back("Retour");
    int j=50, choix;
    for(const auto& elem: propositions)//Affichage des choix
    {
        textout_centre_ex(m_plato, MiddleTitle,elem.c_str(), SCREEN_W/2,SCREEN_H/4+j, makecol(255,200,0),-1);
        j+=85;
    }
    bool fin = false;
    afficher();
    while (!fin)//Attente que l'utilisateur fasse son choix
    {

        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+50 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+140)
        {
            choix = 1;//Sous-menu de créateur de carted
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+60,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+60,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+145 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+225)
        {
            choix = 2;//Affichage des 7 meilleurs joueurs du jeu
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+155,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+155,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-350 && mouse_y>=SCREEN_H/4+230 && mouse_x<=SCREEN_W/2+350 &&mouse_y<=SCREEN_H/4+310)
        {
            choix = 3;//retour au menu principal
            masked_blit(arrow1,m_plato,0,0,SCREEN_W/2-450,SCREEN_H/4+240,SCREEN_W,SCREEN_H);//flèches accentuant la sélection de l'utilisateur
            masked_blit(arrow2,m_plato,0,0,SCREEN_W/2+300,SCREEN_H/4+240,SCREEN_W,SCREEN_H);
            afficher();
            rest(250);
            fin = true;
        }
    }
    return choix;
}

void Terrain::affDeck(Deck deck, unsigned int page)///Méthode d'affichage d'un grand deck sur plusieurs page de 5 cartes
{
    FONT *old = load_font("Fonts/Old.pcx",NULL,NULL);//police utilisée
    effacer();
    std::vector<Carte*> vec = deck.getDeck();//récupération des cartes dans un vector
    while(vec.size()%5 != 0)
    {
        vec.push_back(new Carte);
    }
    unsigned int maxpage = vec.size()-5;
    //boutton retour
    rectfill(m_plato, SCREEN_W/2-50, 3*SCREEN_H/4+25, SCREEN_W/2+50, 3*SCREEN_H/4+75, makecol(160,108,61));
    textout_centre_ex(m_plato, old,"Retour", SCREEN_W/2,3*SCREEN_H/4+30, makecol(200,200,200),-1);
    //rectangles contenants les numéros des cartes
    rectfill(m_plato, SCREEN_W/2-700, SCREEN_H/4-150, SCREEN_W/2-600, SCREEN_H/4-100, makecol(160,108,61)); //1
    rectfill(m_plato, SCREEN_W/2-375, SCREEN_H/4-150, SCREEN_W/2-275, SCREEN_H/4-100, makecol(160,108,61)); //2
    rectfill(m_plato, SCREEN_W/2-50, SCREEN_H/4-150, SCREEN_W/2+50, SCREEN_H/4-100, makecol(160,108,61));   //3
    rectfill(m_plato, SCREEN_W/2+275, SCREEN_H/4-150, SCREEN_W/2+375, SCREEN_H/4-100, makecol(160,108,61)); //4
    rectfill(m_plato, SCREEN_W/2+600, SCREEN_H/4-150, SCREEN_W/2+700, SCREEN_H/4-100, makecol(160,108,61)); //5
    //bouttons de page précédente et suivante
    if(page>1)rectfill(m_plato, 25, 3*SCREEN_H/4, 230, 3*SCREEN_H/4+75, makecol(160,108,61));
    if(page<maxpage)rectfill(m_plato, SCREEN_W-200, 3*SCREEN_H/4, SCREEN_W-25, 3*SCREEN_H/4+75, makecol(160,108,61));
    if(page>1)textout_ex(m_plato, old,"Page precedente", 30, 3*SCREEN_H/4+15, makecol(200,200,200),-1);
    if(page<maxpage) textout_right_ex(m_plato, old,"Page suivante", SCREEN_W-30, 3*SCREEN_H/4+15, makecol(200,200,200),-1);
    int j = 3;
    int k = page;
    for(unsigned int i=page-1; i<page+4; i++)//affichage des cartes
    {
        affCarte(j, SCREEN_H/4-75, vec[i]);
        textout_centre_ex(m_plato, old,(std::to_string(k)).c_str(), SCREEN_W/2-657+j,SCREEN_H/4-140, makecol(200,200,200),-1);
        j+=325; k++;
    }
    bool fin = false;
    afficher();
    rest(250);
    while(!fin)//attente que l'utilisateur choisisse de quitter ou appui sur [ECHAP]
    {
        if ( mouse_b&1 && mouse_x>=25 && mouse_y>=3*SCREEN_H/4 && mouse_x<=230 &&mouse_y<=3*SCREEN_H/4+75 && page>1 && !fin)
        {
            affDeck(deck, page-5);
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W-200 && mouse_y>=3*SCREEN_H/4 && mouse_x<=SCREEN_W-25 &&mouse_y<=3*SCREEN_H/4+75 && page<maxpage && !fin)
        {
            affDeck(deck, page+5);
        }
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-50 && mouse_y>=3*SCREEN_H/4+25 && mouse_x<=SCREEN_W/2+50 &&mouse_y<=3*SCREEN_H/4+75 && !fin)
        {
            fin=true;
            break;
        }
        if (key[KEY_ESC])
        {
            fin=true;
            break;
        }
    }
}

void Terrain::argent(int argent)///Affichage des coins du joueur en bas à droite de l'écran
{
    //police
    FONT *old = load_font("Fonts/Old.pcx",NULL,NULL);
    //zone d'affichage (cercle)
    circlefill(m_plato, SCREEN_W-190, 3*SCREEN_H/4+30, 65, makecol(180,140,0));
    //Affichage des informations
    textout_centre_ex(m_plato, old,"Vos coins:", SCREEN_W-190,3*SCREEN_H/4+10, makecol(200,200,200),-1);
    textout_centre_ex(m_plato, old,(std::to_string(argent)).c_str(), SCREEN_W-190,3*SCREEN_H/4+30, makecol(200,200,200),-1);
}

void Terrain::regles(std::vector<std::string> regles)//affichage des règles ou des crédits sur un panneau au dessus du menu principal
{
    effacer();
    //Chargement des polices
    FONT *old = load_font("Fonts/regles.pcx",NULL,NULL);
    FONT *MainTitle = load_font("Fonts/MainTitle.pcx",NULL,NULL);

    //Chargement de la banière de titre et affichage du titre
    BITMAP* baniere = load_bitmap_check("img/Baniere.bmp");
    masked_blit(baniere,m_plato,0,0,SCREEN_W/2-566,0,SCREEN_W,SCREEN_H);
    textout_centre_ex(m_plato, MainTitle,"Batailles        d'Etats", SCREEN_W/2,SCREEN_H/4-75, makecol(255,200,0),-1);
    textout_centre_ex(m_plato, MainTitle," & coups", SCREEN_W/2+7,SCREEN_H/4-90, makecol(255,200,0),-1);
    //Affichage du panneau
    BITMAP* planche = load_bitmap_check("img/regles.bmp");
    masked_blit(planche,m_plato,0,220,SCREEN_W/2-750,0,SCREEN_W,SCREEN_H);
    int j = 25, w = j;
    for(const auto& elem:regles)//Affichage du texte donné
    {
        textout_centre_ex(m_plato, old,elem.c_str(), SCREEN_W/2, SCREEN_H/4+20+w, makecol(255,255,255),-1);
        w+=j;
    }
    //Boutton retour
    rectfill(m_plato, 25, SCREEN_H-80, 125, SCREEN_H-25, makecol(160,108,61));
    textout_centre_ex(m_plato, old,"Retour", 75,SCREEN_H-75, makecol(200,200,200),-1);
    bool fin = false;
    afficher();
    while(!fin)//Attends que l'utilisateur appuie sur retour ou sur sa touche [ECHAP]
    {
        if ( mouse_b&1 && mouse_x>=25 && mouse_y>=SCREEN_H-80 && mouse_x<=125 &&mouse_y<=SCREEN_H-25 && !fin)
        {
            fin=true;
            break;
        }
        if (key[KEY_ESC])
        {
            fin=true;
            break;
        }
    }
}

void Terrain::standby()///attente que l'utilisateur clique sur fermer ou appuie sur [ECHAP]
{
    //Police
    FONT *old = load_font("Fonts/regles.pcx",NULL,NULL);
    //Boutton retour
    rectfill(m_plato, SCREEN_W/2-50, SCREEN_H-45, SCREEN_W/2+50, SCREEN_H, makecol(160,108,61));
    textout_centre_ex(m_plato, old,"Retour", SCREEN_W/2,SCREEN_H-40, makecol(200,200,200),-1);
    bool fin = false;
    afficher();
    rest(250);
    while(!fin)//attente que l'utilisateur clique sur fermer ou appuie sur [ECHAP]
    {
        if ( mouse_b&1 && mouse_x>=SCREEN_W/2-50 && mouse_y>=SCREEN_H-50 && mouse_x<=SCREEN_W/2+50 &&mouse_y<=SCREEN_H && !fin)
        {
            fin=true;
            break;
        }
        if (key[KEY_ESC])
        {
            fin=true;
            break;
        }
    }
}
