#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <filesystem>
#include <string>

#include "classes/objets.hpp"

using namespace std;


int get_distance(string villeA, string villeB, vector<string> nomVilles, vector<vector<int>> matriceDistance){
    int idVilleB, idVilleA;

    auto it = find (nomVilles.begin(), nomVilles.end(), villeA);
    if (it != nomVilles.end()){
        idVilleA = it - nomVilles.begin();
    }

    it = find (nomVilles.begin(), nomVilles.end(), villeB);
    if (it != nomVilles.end()){
        idVilleB = it - nomVilles.begin();
    }

    return matriceDistance[idVilleA][idVilleB];
}

int main(int argc, char** argv)
{
    // Mauvais paramètres de lancement
    if (argc != 3)
    {
        cerr << "Format incorrect ./TP5 fichier_colis.txt fichier_villes.txt" << endl;
        return EXIT_FAILURE;
    }

    // On récupère les deux arguments
    string pathColis = argv[1];
    string pathVilles = argv[2];

    //Si les fichiers n'existent pas
    if (!filesystem::exists(pathColis) || !filesystem::exists(pathVilles))
    {
        cerr << "Erreur un des fichiers n'existe pas, veuillez vérifier" << endl;
        return EXIT_FAILURE;
    }


    Colis colisObj(pathColis);
    Villes villesObj(pathVilles);

    cout << colisObj << endl;
    cout << villesObj << endl;


    return EXIT_SUCCESS;
}