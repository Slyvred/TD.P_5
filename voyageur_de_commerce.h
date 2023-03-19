#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>

constexpr int codeASCIIde_a = 97;
constexpr int codeASCIIde_A = 65;
constexpr int nombreDeLettres = 26;
constexpr int tailleMinNomVille = 4;
constexpr int tailleMaxNomVille = 12;
constexpr int grainePourLeRand = 1;
constexpr int nombreDeVilles = 8;
constexpr int nombreCombinaisons = 24;
constexpr int tailleCoteCarte = 100;

typedef struct Vec2
{
    int x, y;
    friend std::ostream &operator<<(std::ostream &os, struct Vec2 &vec)
    {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
} vec2;

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &vec)
{
    for (auto &it : vec)
        os << it << " ";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::map<std::string, std::tuple<T, T, T>> &map)
{
    for (auto &[key, value] : map)
        os << key << "(" << get<0>(value) << ", " << get<1>(value) << ", " << get<2>(value) << ") ";
    return os;
}

template <typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &os, std::array<std::array<T, SIZE>, SIZE> &arr)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            os << std::setw(3) << arr[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

void toutesLesPermutations(std::vector<std::string> &villes, int debut, int fin);

float dstEuclidienne(const vec2 &a, const vec2 &b);

int rangedRand(int min, int max);

void genNomsDeVilles(std::vector<std::string> &nomVilles, std::map<std::string, std::tuple<int, int, int>> &mapVillesPos);

float calcDist(const std::map<std::string, std::tuple<int, int, int>> &mapVillesPos, std::vector<std::string> &nomVilles);
// float calcDist(const std::array<std::array<int, nombreDeVilles>, nombreDeVilles>& DIST);

void getBestDist(std::vector<std::string> &villes, std::map<std::string, std::tuple<int, int, int>> &mapVillesPos, int debut, int fin);

std::array<std::array<int, nombreDeVilles>, nombreDeVilles> genMatriceDst(std::map<std::string, std::tuple<int, int, int>> &mapVillesPos);