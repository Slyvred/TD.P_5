#pragma once
#include "objets.hpp"
using namespace std;

typedef struct SolVille
{
    vector<string> tournee;
    int distanceTotale = INT32_MAX;
} solVille;

class Villes
{
private:
    vector<string> nomVilles;
    vector<vector<int>> matriceDistance;
    int nbVilles;

public:
    Villes(const string &path);
    friend ostream &operator<<(ostream &os, Villes &villes);
    int getDistance(string &villeA, string &villeB);
    solVille getBestPath();
    int getTotalDistance(vector<string> &solution);
    solVille getBestPathRepl(int n); // n notre nombre de réplications
    void genVilles(int nbVilles, const string& nomFichier);
};