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

vector<string> Villes::getBestPath()
{
    int distanceTotale = 0;

    // Contient notre paire de solution
    string bestVille, oBestVille;
    int bestDist = 999, oBestDist = 999;

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
        bestDist = 999;
    }
    cout << "Distance totale: " << distanceTotale << endl;
    return solution;
}