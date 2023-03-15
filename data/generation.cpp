#include "generation.h"

void genVilles(int nbVille, const string& nomFichier)
{
    srand(rand() % 100);

    std::string tmpVille;
    int nbLettresNomVille = 0;

    // On ouvre le fichier txt
    ofstream myfile(nomFichier.c_str());

    // On ajoute le nombre de ville dans le fichier
    if (myfile)
    {
        myfile << nbVille << endl;
    } else {
        cerr << "Unable to open file." << endl;
    }

    for (int i = 0; i < nbVille; i++)
    {
        // On détermine notre nombre de lettres pour la ville i
        nbLettresNomVille = rand()%8 + 2;

        for (int j = 0; j < nbLettresNomVille; j++)
        {
            // On génénère une lettre majuscule entre A et Z
            if (j == 0)
            {
                tmpVille += codeASCIIde_A + rand() % (nbLettresNomVille);
            }
            // On génénère une lettre minuscule entre a et z
            tmpVille += codeASCIIde_a + rand() % (nbLettresNomVille - 1);
        }
        // On met les noms des villes dans le fichier

        if (myfile)
        {
            myfile << tmpVille << endl;
        } else {
            cerr << "Unable to open file." << endl;
        }

        // On clear le buffer pour recommencer
        tmpVille.clear();
    }

    // ecriture de la matrice des coordonnées
    vector<vector<int>> matriceDistance;

    for (int i = 0; i < nbVille - 1; i++)
    {
        for (int j = i + 1; j < nbVille - 1; j++)
        {
            if (i == j) matriceDistance[i][j] = 0;

            // On génénère une distance aléatoire
            int d = 10 + rand() % 100;
            matriceDistance[i][j] = d;
            matriceDistance[j][i] = d;
        }
    }
    if (myfile)
    {
        for (auto i = 0; i < nbVille - 1; i++)
        {
            for (auto j = 0; j < nbVille - 1; j++)
            {
                myfile << matriceDistance[i][j] << " ";
            }
            myfile << endl;
        }
    } else
    {
        cerr << "Unable to open file." << endl;
    }

    // On ferme le fichier
    myfile.close();
}
