#include "colis.hpp"
#include <algorithm>
using namespace std;


Colis::Colis(const string &path)
{
    ifstream file(path);

    try
    {
        if (file.is_open())
        {
            string buff;

            // Buff contient une ligne du fichier
            while (getline(file, buff))
            {
                auto str = split(buff, ' ');
                objet tmpObj;

                // Première ligne du fichier -> capacité et nombre obj
                if (str.size() == 2)
                {
                    capacite = stoi(str[0]);
                    nombreObj = stoi(str[1]);
                    continue;
                }

                float ratio = stof(str[2]) / stof(str[1]); // ratio bénéfice/conso
                tmpObj = {stoi(str[0]), stoi(str[1]), stoi(str[2]), ratio};
                objets.push_back(tmpObj);
            }
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

ostream &operator<<(ostream &os, struct Colis &colis)
{
    os << "Capacité: " << colis.capacite << endl;
    os << "Nombre d'objets: " << colis.nombreObj << endl;

    for (auto &obj : colis.objets)
    {
        os << obj;
    }
    return os;
}

vector<objet> Colis::getBestShipment()
{
    int consoTotale = 0, benefTotal = 0;
    vector<objet> solution;

    // On trie le vector en fonction du ratio dans l'ordre décroissant
    sort(objets.begin(), objets.end(), [](objet objA, objet objB)
         { return objA.ratio > objB.ratio; });

    for (auto it = objets.begin(); it != objets.end() - 1; it++)
    {
        auto obj1 = *it;
        auto obj2 = *(it + 1);
        auto sol = obj1;

        // À optimiser, c'est dégueulasse
        // Si notre couple de solutions est invalide, on continue
        if (obj1.conso + consoTotale > capacite && obj2.conso + consoTotale > capacite)
            continue;
        // Si l'objet 1 prend trop de place, on sélectionne le deuxième
        else if (obj1.conso + consoTotale > capacite)
            sol = obj2;
        // Si les deux objets vont, on en choisit un aléatoirement
        else if (obj2.conso + consoTotale <= capacite && obj2.conso + consoTotale <= capacite)
            sol = (rand() % 2 == 0) ? obj1 : obj2;
        // Sinon, sol ne change pas et reste obj1

        if (find(solution.begin(), solution.end(), sol) != solution.end())
            continue;

        // On ajoute l'objet sélectionné
        solution.push_back(sol);
        consoTotale += sol.conso;
        benefTotal += sol.benefice;
    }

    cout << "Bénéfice: " << benefTotal << endl;
    cout << "Consommation: " << consoTotale << endl;
    return solution;
}