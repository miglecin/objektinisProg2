#ifndef VERSIJOSFUNKC_H
#define VERSIJOSFUNKC_H

#include <vector>
#include <list>
#include <deque>
#include <string>

template <typename T = std::vector<float>>
struct studentas {
    std::string Vard;
    std::string Pav;
    T nd;  // ND konteineris (pvz., vector, list, deque)
    int egz;
    double Gal;
};


template <typename T = std::vector<float>>  // T gali būti vector, list, deque
double generuotiGalvid(const T& nd, int egz);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
double generuotiGalmed(const T& nd, int egz);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
double pasirinktasGal(const T& nd, int egz, char kaip);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
void randomPaz(T& nd, int& egz, int kiek_nd);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
void nuskaitymasFile(std::vector<studentas<T>>& grupe, const std::string& filename);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
void spausdintiRez(std::vector<studentas<T>>& grupe, bool iFaila, char pasirinkimas, const std::string& failoPavadinimas);

template <typename T = std::vector<float>>  // T gali būti vector, list, deque
void rusiuotiStud(std::vector<studentas<T>>& grupe, char rusiavimoPas);

#endif
