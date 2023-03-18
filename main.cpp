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
    if (argc != 4 && argc != 3)
    {
        cerr << "Formats corrects:" << endl;
        cout << "./TP5 graine fichier_colis.txt fichier_villes.txt" << endl;
        cout << "./TP5 -1 fichier_resultat.txt" << endl;
        return EXIT_FAILURE;
    }
    // Mode génération
    else if (argc == 3 && atoi(argv[1]) == -1)
    {
        Colis colisObj;
        Villes villesObj;
        string pathRes = argv[2];

        if (!filesystem::exists(pathRes))
        {
            cerr << "Erreur le fichier n'existe pas, veuillez vérifier" << endl;
            return EXIT_FAILURE;
        }

        auto sol = colisObj.getBestShipmentRepl(pathRes);
        cout << 0 << " " << sol.benef << " " << sol.conso << " ";
        for (auto &it : sol.objets)
            cout << it.index << " " << it.conso << " " << it.benefice << " ";

        auto solRep = villesObj.getBestPathRepl(pathRes);
        for (auto &it : solRep.tournee)
            cout << it << " ";
        cout << solRep.distanceTotale << endl;

        return EXIT_SUCCESS;
    }

    // Seed
    unsigned int seed = atoi(argv[1]);
    srand(seed);

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

    // output de la forme: seed benef conso objet1 objet2 ... objet_n ville1 ville2 ... ville_n distance
    cout << seed << " ";
    auto sol = colisObj.getBestShipment();
    cout << sol.benef << " " << sol.conso << " ";
    for (auto &it : sol.objets)
        cout << it.index << " " << it.conso << " " << it.benefice << " ";

    auto sol2 = villesObj.getBestPath();
    for (auto &it : sol2.tournee)
        cout << it << " ";
    cout << sol2.distanceTotale << endl;

    // villesObj.genVilles(4, "out.txt");
    // colisObj.genShipment(20, 4, "test.txt");

    return EXIT_SUCCESS;
}