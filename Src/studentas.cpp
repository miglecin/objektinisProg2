#include "studentas.h"

// Konstruktoriaus realizacija
template <typename T>
Studentas<T>::Studentas(std::istream& is) {
    readStudent(is);
}

// Konstruktoriaus realizacija (default)
template <typename T>
Studentas<T>::Studentas() : egzaminas_(0), galutinis_balas_(0) {}

// Funkcija, skaičiuojanti galutinį balą
template <typename T>
double Studentas<T>::galBalas(double (*balasFunkcija)(const T&) /*= generuotiGalvid*/) const {
    return balasFunkcija(nd_);
}

// Statinės funkcijos realizacija
template <typename T>
void Studentas<T>::rusiuotiStud(std::vector<Studentas<T>>& grupe, char rusiavimoPas) {
    if (rusiavimoPas == 'v') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas<T>& a, const Studentas<T>& b) {
            return a.vardas_ < b.vardas_;
        });
    } else if (rusiavimoPas == 'p') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas<T>& a, const Studentas<T>& b) {
            return a.pavarde_ < b.pavarde_;
        });
    } else if (rusiavimoPas == 'g') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas<T>& a, const Studentas<T>& b) {
            return a.galutinisBalsas() > b.galutinisBalsas();
        });
    }
}

// Nuskaitymo funkcija, kuri nuskaito studentus iš failo
template <typename T>
void Studentas<T>::nuskaitymasFile(std::vector<Studentas<T>>& grupe, const std::string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::string eilute;
    getline(failas, eilute);  // praleidžiame pirmą eilutę (antraštę)

    Studentas<T> laik;
    while (getline(failas, eilute)) {
        std::istringstream ss(eilute);
        laik.readStudent(ss);  // Naudojame readStudent funkciją, kad užpildytume studentą
        grupe.push_back(laik);  // Pridedame studentą į grupę
    }

    failas.close();
}

// Funkcija, skaičiuojanti galutinį balą pagal vidurkį
template <typename T>
double generuotiGalvid(const T& nd, int egz) {
    double suma = std::accumulate(nd.begin(), nd.end(), 0.0);
    return 0.4 * (suma / nd.size()) + 0.6 * egz;
}

// Funkcija, skaičiuojanti galutinį balą pagal medianą
template <typename T>
double generuotiGalmed(const T& nd, int egz) {
    std::vector<double> sorted = nd;
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    double mediana = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    return 0.4 * mediana + 0.6 * egz;
}

// Instancijacija, kad kompiliatorius žinotų, ką kompiliuoti
template class Studentas<std::vector<double>>;
template class Studentas<std::list<double>>;
template class Studentas<std::deque<double>>;

// Instancijavimas, kad kompiliatorius žinotų, ką sukompiliuoti
template double generuotiGalvid<std::vector<double>>(const std::vector<double>&, int);
template double generuotiGalmed<std::vector<double>>(const std::vector<double>&, int);

template double generuotiGalvid<std::list<double>>(const std::list<double>&, int);
template double generuotiGalmed<std::list<double>>(const std::list<double>&, int);

template double generuotiGalvid<std::deque<double>>(const std::deque<double>&, int);
template double generuotiGalmed<std::deque<double>>(const std::deque<double>&, int);