#include <vector>
using namespace std;

typedef struct Objet
{
    // pas d'index car on le retrouve dans le vecteur ci-dessous
    int conso, benefice;
}objet;

typedef struct Vehicule
{
    int capacite, nombreObj;
    vector<objet> objets;
}vehicule;