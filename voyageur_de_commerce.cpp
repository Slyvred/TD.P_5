#include "voyageur_de_commerce.h"

void toutesLesPermutations(std::vector<std::string> &villes, int debut, int fin)
{
    if (debut == fin)
    {
        std::cout << villes << std::endl;
    }
    else
    {
        // Permutations made
        for (int i = debut; i <= fin; i++)
        {
            // echange des deux villes
            swap(villes[debut], villes[i]);
            // Appel Recursif
            toutesLesPermutations(villes, debut + 1, fin);
            // On revient à la situation précédente
            swap(villes[debut], villes[i]);
        }
    }
}

float dstEuclidienne(const vec2 &a, const vec2 &b)
{
    // return (float)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return hypot(a.x - b.x, a.y - b.y);
}

int rangedRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void genNomsDeVilles(std::vector<std::string> &nomVilles, std::map<std::string, std::tuple<int, int, int>> &mapVillesPos)
{
    std::string tmpVille;
    int nbLettresNomVille = 0;
    for (int i = 0; i < nombreDeVilles; i++)
    {
        // On détermine notre nombre de lettres pour la ville i
        nbLettresNomVille = rangedRand(tailleMinNomVille, tailleMaxNomVille);

        for (int j = 0; j < nbLettresNomVille; j++)
        {
            // On génénère une lettre majuscule entre A et Z
            if (j == 0)
            {
                tmpVille += rangedRand(codeASCIIde_A, (codeASCIIde_A + nbLettresNomVille - 1));
            }

            // On génénère une lettre minuscule entre a et z
            tmpVille += rangedRand(codeASCIIde_a, (codeASCIIde_a + nbLettresNomVille - 1));
        }

        // On créé notre position
        vec2 pos = {rand() % tailleCoteCarte, rand() % tailleCoteCarte};

        // On insère villes et pos dans les structures de données correspondantes
        mapVillesPos.insert({tmpVille, {i, pos.x, pos.y}});
        nomVilles.push_back(tmpVille);

        // On clear le buffer pour recommencer
        tmpVille.clear();
    }
}

// float calcDist(const std::array<std::array<int, nombreDeVilles>, nombreDeVilles>& DIST)
float calcDist(const std::map<std::string, std::tuple<int, int, int>> &mapVillesPos, std::vector<std::string> &nomVilles)
{
    float dst = 0;
    for (auto it = nomVilles.begin(); it != nomVilles.end() - 1; it++)
    {
        auto villeA = mapVillesPos.at(*it);
        auto villeB = mapVillesPos.at(*(it + 1));

        vec2 posA = {std::get<1>(villeA), std::get<2>(villeA)};
        vec2 posB = {std::get<1>(villeB), std::get<2>(villeB)};

        dst += dstEuclidienne(posA, posB);
    }
    return dst;
}


void getBestDist(std::vector<std::string> &villes, std::map<std::string, std::tuple<int, int, int>> &mapVillesPos, int debut, int fin)
{
    static float bestDist = FLT_MAX;

    if (debut == fin)
    {
        float dst = calcDist(mapVillesPos, villes);
        if (dst <= bestDist)
        {
            bestDist = dst;

            std::cout << "Meilleur trajet: " << villes;
            std::cout << "\tDistance totale: " << bestDist << " km" << std::endl;
        }
    }
    else
    {
        // Permutations made
        for (int i = debut; i <= fin; i++)
        {
            // echange des deux villes
            swap(villes[debut], villes[i]);
            // Appel Recursif
            getBestDist(villes, mapVillesPos, debut + 1, fin);
            // On revient à la situation précédente
            swap(villes[debut], villes[i]);
        }
    }
}

std::array<std::array<int, nombreDeVilles>, nombreDeVilles> genMatriceDst(std::map<std::string, std::tuple<int, int, int>> &mapVillesPos)
{
    std::array<std::array<int, nombreDeVilles>, nombreDeVilles> DIST;
    int x = 0, y = 0;
    // On va itérer dans notre map de villes et calculer la dst pour chaque ville
    for (auto &[keyA, valueA] : mapVillesPos)
    {
        // On récupère la position
        vec2 posA = {std::get<1>(valueA), std::get<2>(valueA)};
        for (auto &[keyB, valueB] : mapVillesPos)
        {
            vec2 posB = {std::get<1>(valueB), std::get<2>(valueB)};
            DIST[x][y] = dstEuclidienne(posA, posB);
            y++;
        }
        x++;
        y = 0;
    }
    return DIST;
}