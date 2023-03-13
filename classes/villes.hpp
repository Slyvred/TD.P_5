#pragma once
#include "objets.hpp"
using namespace std;


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