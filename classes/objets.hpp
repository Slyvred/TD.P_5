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

    friend ostream &operator<<(ostream &os, struct Objet &obj)
    {
        os << "\tIndex: " << obj.index << endl;
        os << "\tConsommation: " << obj.conso << endl;
        os << "\tBénéfice: " << obj.benefice << endl
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
};