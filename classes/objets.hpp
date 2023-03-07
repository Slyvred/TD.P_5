#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
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

typedef struct VillesDst
{
    vector<string> nomVilles;
    vector<vector<int>> matriceDistance;
    int nbVilles;

    friend ostream& operator<<(ostream& os, struct VillesDst& villesDst)
    {
        os << "Nombre de villes: " << villesDst.nbVilles << endl;
        os << "Villes: " << endl;

        for (auto &ville : villesDst.nomVilles)
        {
            os << "\t" << ville << endl;
        }

        os << "Matrice:" << endl;

        for (auto i = 0; i < villesDst.matriceDistance[0].size(); i++)
        {
            os << "\t";
            for (auto j = 0; j < villesDst.matriceDistance[0].size(); j++)
            {
                os << setw(2) << villesDst.matriceDistance[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
}villesDst;

colis readColis(string& path);
villesDst readVilles(string& path);