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
    float ratio; // ratio bénéfice/conso

    friend ostream &operator<<(ostream &os, struct Objet &obj)
    {
        os << "Index: " << obj.index << endl;
        os << "Consommation: " << obj.conso << endl;
        os << "Bénéfice: " << obj.benefice << endl;
        os << "Ratio Bénéf/Conso: " << obj.ratio << endl
           << endl;

        return os;
    }
} objet;
class Colis
{
private:
    int capacite, nombreObj;
    vector<objet> objets;

public:
    Colis(const string &path);
    vector<objet> getBestShipment();
    friend ostream &operator<<(ostream &os, Colis &colis);
};

class Villes
{
private:
    vector<string> nomVilles;
    vector<vector<int>> matriceDistance;
    int nbVilles;

public:
    Villes(const string &path);
    friend ostream &operator<<(ostream &os, Villes &villes);
    int getDistance(string villeA, string villeB);
    vector<string> getBestPath();
};