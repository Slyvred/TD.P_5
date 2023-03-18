#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <filesystem>
#include <string>

#include "classes/objets.hpp"
#include "classes/colis.hpp"
#include "classes/villes.hpp"
#include "data/generation.h"

using namespace std;

int main(int argc, char **argv)
{
    //     genVilles(4, R"(C:\Users\Administrateur\CLionProjects\algo\TD.P_5\data\example.txt)");
    //     return EXIT_SUCCESS;
    // }
    // Mauvais paramètres de lancement
    if (argc != 4)
    {
        cerr << "Format incorrect ./TP5 graine fichier_colis.txt fichier_villes.txt" << endl;
        return EXIT_FAILURE;
    }

    // Seed
    unsigned int seed = atoi(argv[1]);
    srand(seed);
    cout << "Seed: " << seed << endl;

    // On récupère les deux arguments
    string pathColis = argv[2];
    string pathVilles = argv[3];

    // Si les fichiers n'existent pas
    if (!filesystem::exists(pathColis) || !filesystem::exists(pathVilles))
    {
        cerr << "Erreur un des fichiers n'existe pas, veuillez vérifier" << endl;
        return EXIT_FAILURE;
    }

    Colis colisObj(pathColis);
    Villes villesObj(pathVilles);
    const int nbRepl = 100;

    cout << "Solution: " << endl;

    auto sol = colisObj.getBestShipmentRepl(nbRepl);
    cout << "(" << sol.benef << ", " << sol.conso << ")" << endl;

    auto sol2 = villesObj.getBestPathRepl(nbRepl);
    cout << "(";
    for (auto &it : sol2.tournee)
        cout << it << " ";

    cout << ", " << sol2.distanceTotale << ")" << endl;

    villesObj.genVilles(4, "out.txt");
    colisObj.genShipment(20, 4, "test.txt");

    return EXIT_SUCCESS;
}