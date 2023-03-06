#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <filesystem>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // Mauvais paramètres de lancement
    if (argc != 3)
    {
        cerr << "format correct ./TP5 fichier_colis.txt fichier_villes.txt" << endl;
        return EXIT_FAILURE;
    }

    // Si les fichiers n'existent pas
    string pathColis, pathVilles;
    if (!filesystem::exists(pathColis) || !filesystem::exists(pathVilles))
    {
        cerr << "Erreur un des fichiers n'existe pas, veuillez vérifier" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}