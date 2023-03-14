#include "generation.h"

void genNomsDeVilles(int nbVille){
    std::string tmpVille;
    int nbLettresNomVille = 0;

    // On ouvre le fichier txt
    ofstream myfile;
    myfile.open("./example.txt");

    // On ajoute le nombre de ville dans le fichier
    if (myfile.is_open()) {
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
            if (j == 0) {
                tmpVille += codeASCIIde_A + rand() % (nbLettresNomVille);
            }
            // On génénère une lettre minuscule entre a et z
            tmpVille += codeASCIIde_a + rand() % (nbLettresNomVille - 1);
        }
        // On met les noms des villes dans le fichier

        if (myfile.is_open()) {
            myfile << tmpVille << endl;
        } else {
            cout << "Unable to open file." << endl;
        }

        cout << tmpVille;
        // On clear le buffer pour recommencer
        tmpVille.clear();
    }

    // On ferme le fichier
    myfile.close();
}