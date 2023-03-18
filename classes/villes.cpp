#include "villes.hpp"
#include <cmath>
#include <algorithm>
#include <thread>
using namespace std;

Villes::Villes(const string &path)
{
    ifstream file(path);

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

bool isNum(string &str)
{
    for (auto &chr : str)
    {
        if (!isalpha(chr))
            return true;
    }
    return false;
}

solVille Villes::getBestPathRepl(const string &filename)
{
    // Solution finale
    solVille solution;

    ifstream file(filename);

    if (!file.is_open())
        return solution;

    string buff;
    // Buff contient une ligne du fichier
    while (getline(file, buff))
    {
        // DÉCOUPE: MOKTAR !!!!!
        auto str = split(buff, ' ');

        // On crée la solution temporaire
        solVille tmp;

        tmp.distanceTotale = stoi(str.back());
        // On garde que le nom des villes
        str.erase(remove_if(str.begin(), str.end(), isNum), str.end());
        tmp.tournee = str;

        // Si la solution tmp est meilleure que la notre, on remplace
        if (tmp.distanceTotale < solution.distanceTotale)
        {
            solution.distanceTotale = tmp.distanceTotale;
            solution.tournee = tmp.tournee;
        }
    }
    file.close();
    return solution;
}

void Villes::genVilles(int nbVilles, const string &nomFichier)
{
    this->nbVilles = nbVilles;
    nomVilles.clear();
    matriceDistance.clear();

    // Génère ne nombre de villes
    for (int i = 0; i < nbVilles; i++)
    {
        string tmpVille;
        int nbLetter = rangedRand(4, 9);

        for (int j = 0; j < nbLetter; j++)
        {
            tmpVille += (j == 0) ? rangedRand('A', 'Z') : rangedRand('a', 'z');
        }
        nomVilles.push_back(tmpVille);
    }

    // On génère la matrice distance aléatoirement
    matriceDistance.resize(nbVilles);
    for (auto i = 0; i < nbVilles; i++)
        for (auto j = 0; j < nbVilles; j++)
            matriceDistance[i].push_back((i == j) ? 0 : rangedRand(10, 50));

    // On la rend symétrique
    for (auto i = 0; i < nbVilles; i++)
        for (auto j = 0; j <= i; j++)
            matriceDistance[j][i] = matriceDistance[i][j];

    cout << *this << endl;

    ofstream file(nomFichier);

    if (!file.is_open())
        return;

    string buff;

    buff += to_string(nbVilles) + '\n';

    for (auto &ville : nomVilles)
        buff += ville + '\n';

    for (auto i = 0; i < matriceDistance[0].size(); i++)
    {
        for (auto j = 0; j < matriceDistance[0].size(); j++)
        {
            buff += to_string(matriceDistance[i][j]) + ' ';
        }
        buff += '\n';
    }

    file << buff << endl;

    file.close();
}