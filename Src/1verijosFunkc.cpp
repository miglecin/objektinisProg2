#include "1versijosFunkc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

template <typename T>
double generuotiGalvid(const T& nd, int egz) {
    double suma = std::accumulate(nd.begin(), nd.end(), 0.0);
    return 0.4 * (suma / nd.size()) + 0.6 * egz;
}

template <typename T>
double generuotiGalmed(const T& nd, int egz) {
    std::vector<double> sorted = nd;
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    double mediana = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    return 0.4 * mediana + 0.6 * egz;
}

template <typename T>
double pasirinktasGal(const T& nd, int egz, char kaip) {
    if (kaip == 'v') {
        return generuotiGalvid(nd, egz);
    } else if (kaip == 'm') {
        return 0.4 * generuotiGalmed(nd, egz) + 0.6 * egz;
    }
    return 0;
}

template <typename T>
void randomPaz(T& nd, int& egz, int kiek_nd) {
    nd.clear();
    for (int i = 0; i < kiek_nd; i++) {
        nd.push_back(rand() % 10 + 1);
    }
    egz = rand() % 10 + 1;
}

template <typename T>
void nuskaitymasFile(std::vector<studentas<T>>& grupe, const std::string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::string eilute;
    getline(failas, eilute); // praleidžiame pirmą eilutę (antraštę)

    studentas<T> laik;
    while (getline(failas, eilute)) {
        std::istringstream ss(eilute);
        ss >> laik.Vard >> laik.Pav;
        double pazymys;
        laik.nd.clear();
        while (ss >> pazymys) {
            laik.nd.push_back(pazymys);
        }

        if (!laik.nd.empty()) {
            laik.egz = laik.nd.back();
            laik.nd.pop_back();
        }

        grupe.push_back(laik);
    }
    failas.close();
}

template <typename T>
void spausdintiRez(std::vector<studentas<T>>& grupe, bool iFaila, char pasirinkimas, const std::string& failoPavadinimas) {
    for (auto& stud : grupe) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    rusiuotiStud(grupe, 'g');
    if (iFaila) {
        std::ofstream failas(failoPavadinimas);
        if (!failas) {
            std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
            return;
        }

        for (const auto& stud : grupe) {
            failas << stud.Vard << " " << stud.Pav << " " << stud.Gal << std::endl;
        }
        failas.close();
    } else {
        for (const auto& stud : grupe) {
            std::cout << stud.Vard << " " << stud.Pav << " " << stud.Gal << std::endl;
        }
    }
}

template <typename T>
void rusiuotiStud(std::vector<studentas<T>>& grupe, char rusiavimoPas) {
    if (rusiavimoPas == 'v') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) {
            return a.Vard < b.Vard;
        });
    } else if (rusiavimoPas == 'p') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) {
            return a.Pav < b.Pav;
        });
    } else if (rusiavimoPas == 'g') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) {
            return a.Gal > b.Gal;
        });
    }
}

// Explicit instantiation of templates to avoid linker issues
template void nuskaitymasFile<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, const std::string&);
template void nuskaitymasFile<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, const std::string&);
template void nuskaitymasFile<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, const std::string&);

template void spausdintiRez<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, bool, char, const std::string&);
template void spausdintiRez<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, bool, char, const std::string&);
template void spausdintiRez<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, bool, char, const std::string&);
