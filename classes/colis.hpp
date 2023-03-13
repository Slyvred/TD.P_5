#pragma once
#include "objets.hpp"
using namespace std;

typedef struct SolColis
{
    vector<objet> objets;
    int benef = INT32_MIN;
    int conso = INT32_MAX;
}solColis;

class Colis
{
private:
    int capacite, nombreObj;
    vector<objet> objets;

public:
    Colis(const string &path);
    solColis getBestShipment();
    solColis getBestShipmentRepl(int n); // nombre de réplications
    friend ostream &operator<<(ostream &os, Colis &colis);
};