#include "main.cpp"

float calcDist(vector<vector<int>> matriceDistance, vector<string> &villes, vector<string> nomVilles)
{
    float dst = 0;
    for (auto it = villes.begin(); it != villes.end() - 1; it++)
    {
        auto idVilleA = std::find(nomVilles.begin(), nomVilles.end(), it);
        auto idVilleB =

        dst = matriceDistance[idVilleA][idVilleB];
    }
    return dst;
}


void getBestDist(std::vector<std::string> &villes, vector<vector<int>> matriceDistance, int nbVilles)
{
    static float bestDist = FLT_MAX;
    int debut = 0;

    if (debut == nbVilles)
    {
        float dst = calcDist(matriceDistance, villes);
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
        for (int i = debut; i <= nbVilles; i++)
        {
            // echange des deux villes
            swap(villes[debut], villes[i]);
            // Appel Recursif
            getBestDist(villes, matriceDistance, nbVilles);
            // On revient à la situation précédente
            swap(villes[debut], villes[i]);
        }
    }
}
