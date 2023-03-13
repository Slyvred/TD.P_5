#include "villes.hpp"
#include <algorithm>
#include <thread>
using namespace std;

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

int Villes::getDistance(string &villeA, string &villeB)
{
    int idVilleB, idVilleA;
    try
    {
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
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return matriceDistance[idVilleA][idVilleB];
}

solVille Villes::getBestPath()
{
    int distanceTotale = 0;

    // Contient notre paire de solution
    string bestVille, oBestVille;
    int bestDist = INT32_MAX, oBestDist = INT32_MAX;

    // Contient la ville et la distance qui vont être ajoutés
    string solVille;
    int solDist;

    // Point de départ aléatoire
    string start = nomVilles[rand() % nomVilles.size()];
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
                // On conserve la seconde meilleure ville et la seconde meilleure distance
                oBestVille = bestVille;
                oBestDist = bestDist;

                bestDist = dst;
                bestVille = ville;

                // cout << "(" << bestVille << ", " << bestDist << ")\t(" << oBestVille << ", " << oBestDist << ")" << endl;
            }
        }
        // Si une des deux solutions est invalide
        if (bestVille.empty() || oBestVille.empty())
            continue;

        // Tirage aléatoire parmi les deux meilleurs solutions
        auto tirage = rand() % 2;
        solVille = (tirage == 0) ? bestVille : oBestVille;
        solDist = (tirage == 0) ? bestDist : oBestDist;

        // On vérifie que notre solution est valide
        if (find(solution.begin(), solution.end(), solVille) != solution.end())
            continue;

        distanceTotale += getDistance(start, solVille);
        solution.push_back(solVille);

        // On répète le processus en partant de la ville trouvée
        start = solVille;
        bestDist = INT32_MAX;
    }
    return {solution, distanceTotale};
}

int Villes::getTotalDistance(vector<string> &solution)
{
    if (solution.empty())
        return INT32_MAX;

    int dst = 0;

    for (auto it = solution.begin(); it != solution.end() - 1; it++)
    {
        dst += getDistance(*it, *(it + 1));
    }
    return dst;
}

solVille Villes::getBestPathRepl(int n)
{
    solVille solution;

    for (int i = 0; i < n; i++)
    {
        // Si la solution générée est meilleure que la précédente, on la remplace
        auto tmp = getBestPath();
        if (tmp.distanceTotale < solution.distanceTotale)
        {
            solution.distanceTotale = tmp.distanceTotale;
            solution.tournee = tmp.tournee;
        }
        // cout << "(";
        // for (auto &it : tmp.tournee)
        //     cout << it << " ";

        // cout << ", " << tmp.distanceTotale << ")" << endl;
    }
    return solution;
}