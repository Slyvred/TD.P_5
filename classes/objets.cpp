#include "objets.hpp"
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

colis readColis(string path)
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