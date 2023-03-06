#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef struct Objet
{
    // (pas d'index car on le retrouve dans le vecteur ci-dessous)
    int index, conso, benefice;
}objet;

typedef struct Colis
{
    int capacite, nombreObj;
    vector<objet> objets;
}colis;

colis readColis(string path);