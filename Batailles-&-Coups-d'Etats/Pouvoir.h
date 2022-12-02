#ifndef POUVOIR_H_INCLUDED
#define POUVOIR_H_INCLUDED
#include <string>
///Classe gérant les types des pouvoirs
class Pouvoir
{
private:
    std::string m_type;         //Type
public:
    Pouvoir();
    Pouvoir(std::string type);
    ~Pouvoir();
    void afficher() const;      //Affichage du pouvoir
    std::string getNom() const; //Getter pour le nom du type
};

#endif // POUVOIR_H_INCLUDED
