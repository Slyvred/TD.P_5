#pragma once
#include "objets.hpp"
using namespace std;


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