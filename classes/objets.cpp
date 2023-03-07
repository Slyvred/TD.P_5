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

                tmpObj = {stoi(str[0]), stoi(str[1]), stoi(str[2])};
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

Villes::Villes(const string& path)
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