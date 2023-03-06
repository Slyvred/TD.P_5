#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef struct Objet
{
    // (pas d'index car on le retrouve dans le vecteur ci-dessous)
    int index, conso, benefice;

    friend ostream& operator<<(ostream& os, struct Objet& obj)
    {
        os << "\tIndex: " << obj.index << endl;
        os << "\tConsommation: " << obj.conso << endl;
        os << "\tBénéfice: " << obj.benefice << endl << endl;
        
        return os;
    }
}objet;

typedef struct Colis
{
    int capacite, nombreObj;
    vector<objet> objets;

    friend ostream& operator<<(ostream& os, struct Colis& colis)
    {
        os << "Capacité: " << colis.capacite << endl;
        os << "Nombre d'objets: " << colis.nombreObj << endl;

        for (auto &obj : colis.objets)
        {
            os << obj;
        }
        return os;
    }
}colis;

colis readColis(string path);