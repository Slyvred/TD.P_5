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

int main(int argc, char **argv)
{
    srand(time(NULL));
    // Mauvais paramètres de lancement
    if (argc != 3)
    {
        cerr << "Format incorrect ./TP5 fichier_colis.txt fichier_villes.txt" << endl;
        return EXIT_FAILURE;
    }

    // On récupère les deux arguments
    string pathColis = argv[1];
    string pathVilles = argv[2];

    // Si les fichiers n'existent pas
    if (!filesystem::exists(pathColis) || !filesystem::exists(pathVilles))
    {
        cerr << "Erreur un des fichiers n'existe pas, veuillez vérifier" << endl;
        return EXIT_FAILURE;
    }

    Colis colisObj(pathColis);
    Villes villesObj(pathVilles);

    cout << colisObj << endl;
    cout << villesObj << endl;

    cout << "Solution: " << endl;
    auto sol =  colisObj.getBestShipment();
    for (auto &elt : sol)
    {
        cout << elt << " ";
    }
    cout << endl;

    cout << "Solution: " << endl;
    auto sol2 =  villesObj.getBestPath();
    for (auto &elt : sol2)
    {
        cout << elt << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}