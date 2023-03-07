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

colis readColis(string& path)
{
    ifstream file(path);

    colis tmp;

    try
    {
        if (file.is_open())
        {
            string buff;

            // Buff contient une ligne du fichier
            while(getline(file, buff))
            {
                auto str = split(buff, ' ');
                objet tmpObj;

                // Première ligne du fichier -> capacité et nombre obj
                if (str.size() == 2)
                {
                    tmp.capacite = stoi(str[0]);
                    tmp.nombreObj = stoi(str[1]);
                    continue;
                }
                
                tmpObj = {stoi(str[0]), stoi(str[1]), stoi(str[2])};
                tmp.objets.push_back(tmpObj);
            }

            file.close();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return tmp;
}

villesDst readVilles(string& path)
{
    villesDst tmp;
    ifstream file(path);

    try
    {
        if (file.is_open())
        {
            string buff;
            int i = 0;
            // Buff contient une ligne du fichier
            while(getline(file, buff))
            {
                // On le split string en un vector avec ' ' comme séparateur
                auto str = split(buff, ' ');

                // Première ligne du fichier -> nombre de villes
                if (str.size() == 1 && str[0].size() == 1)
                {
                    tmp.nbVilles = stoi(str[0]);
                    tmp.matriceDistance.resize(tmp.nbVilles);
                }
                else if (str.size() >= tmp.nbVilles) // Matrice
                {
                    // On ajoute la ligne
                    for (auto& it: str)
                    {
                        if (it.empty()) continue;
                        tmp.matriceDistance[i].push_back(stoi(it));
                    }
                    i++;
                }
                else // Liste de noms
                {
                    tmp.nomVilles.push_back(str[0]);
                }
            }

            file.close();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return tmp;
}