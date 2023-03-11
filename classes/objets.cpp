#include "objets.hpp"
#include <algorithm>
#include <sstream>

vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream token_stream(str);
    while (getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

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

Villes::Villes(const string &path)
{
    ifstream file(path);

    try
    {
        if (file.is_open())
        {
            string buff;
            int i = 0;
            // Buff contient une ligne du fichier
            while (getline(file, buff))
            {
                // On le split string en un vector avec ' ' comme séparateur
                auto str = split(buff, ' ');

                // Première ligne du fichier -> nombre de villes
                if (str.size() == 1 && str[0].size() == 1)
                {
                    nbVilles = stoi(str[0]);
                    matriceDistance.resize(nbVilles);
                }
                else if (str.size() >= nbVilles) // Matrice
                {
                    // On ajoute la ligne
                    for (auto &it : str)
                    {
                        if (it.empty())
                            continue;
                        matriceDistance[i].push_back(stoi(it));
                    }
                    i++;
                }
                else // Liste de noms
                {
                    nomVilles.push_back(str[0]);
                }
            }

            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

ostream &operator<<(ostream &os, Villes &villes)
{
    os << "Nombre de villes: " << villes.nbVilles << endl;
    os << "Villes: " << endl;

    for (auto &ville : villes.nomVilles)
    {
        os << "\t" << ville << endl;
    }

    os << "Matrice:" << endl;

    for (auto i = 0; i < villes.matriceDistance[0].size(); i++)
    {
        os << "\t";
        for (auto j = 0; j < villes.matriceDistance[0].size(); j++)
        {
            os << setw(2) << villes.matriceDistance[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

int Villes::getDistance(string villeA, string villeB)
{
    int idVilleB, idVilleA;

    auto it = find(nomVilles.begin(), nomVilles.end(), villeA);
    if (it != nomVilles.end())
    {
        idVilleA = it - nomVilles.begin();
    }

    it = find(nomVilles.begin(), nomVilles.end(), villeB);
    if (it != nomVilles.end())
    {
        idVilleB = it - nomVilles.begin();
    }

    return matriceDistance[idVilleA][idVilleB];
}

vector<objet> Colis::getBestShipment()
{
    int consoTotale = 0, benefTotal = 0;
    vector<objet> solution;

    // On trie le vector en fonction du ratio dans l'ordre décroissant
    sort(objets.begin(), objets.end(), [](objet objA, objet objB)
         { return objA.ratio > objB.ratio; });

    for (auto &obj : objets)
    {
        // Si on ne peut pas le mettre dans le coffre, on passe au suivant
        if (obj.conso + consoTotale > capacite)
            continue;

        solution.push_back(obj);
        consoTotale += obj.conso;
        benefTotal += obj.benefice;
    }
    cout << "Bénéfice: " << benefTotal << endl;
    cout << "Consommation: " << consoTotale << endl;
    return solution;
}

vector<string> Villes::getBestPath()
{
    // Point de départ aléatoire
    string start = nomVilles[rand() % nomVilles.size()];

    // Meilleure distance et ville
    int bestDist = INT32_MAX, distanceTotale = 0;
    string bestVille;

    vector<string> solution;
    solution.push_back(start);

    while (solution.size() != nbVilles)
    {
        // On cherche la distance la plus courte pour aller à la ville suivante
        for (auto &ville : nomVilles)
        {
            // Si la ville a déjà été traitée
            if (find(solution.begin(), solution.end(), ville) != solution.end())
                continue;

            auto dst = getDistance(start, ville);

            if (dst <= bestDist)
            {
                bestDist = dst;
                bestVille = ville;
            }
        }
        // On ajoute la meilleure ville et on passe à la suivante
        distanceTotale += getDistance(start, bestVille);
        solution.push_back(bestVille);
        start = bestVille;
        bestDist = INT32_MAX;
    }
    cout << "Distance totale: " << distanceTotale << endl;
    return solution;
}