#include "studentas.h"

// Konstruktoriaus realizacija
template <typename T>
Studentas<T>::Studentas(std::istream& is) {
    readStudent(is);
}

// Konstruktoriaus realizacija (default)
template <typename T>
Studentas<T>::Studentas() : egzaminas_(0), galutinis_balas_(0) {}

// Generuoja galutinį balą pagal vidurkį
template <typename T>
float generuotiGalvid(const T& nd, int egz) {
    float suma = std::accumulate(nd.begin(), nd.end(), 0.0f);
    float vidurkis = suma / nd.size();
    return 0.4f * vidurkis + 0.6f * egz;
}

// Generuoja galutinį balą pagal medianą
template <typename T>
float generuotiGalmed(const T& nd, int egz) {
    std::vector<float> sorted(nd.begin(), nd.end());
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    float mediana = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    return 0.4f * mediana + 0.6f * egz;
}

// Funkcija, skaičiuojanti galutinį balą
template <typename T>
float Studentas<T>::galBalas(float (*balasFunkcija)(const T&, int) /*= generuotiGalvid*/) const {
    return balasFunkcija(nd_, egzaminas_);
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
        if (ss) {  // Tikriname, ar eilutė buvo sėkmingai nuskaityta
            laik.readStudent(ss);  // Naudojame readStudent funkciją, kad užpildytume studentą
            grupe.push_back(laik);  // Pridedame studentą į grupę
        } else {
            std::cerr << "Klaida nuskaityti eilutę: " << eilute << std::endl;
        }
    }

    failas.close();
}



// Instancijavimas generuotiGalvid funkcijos su įvairiais konteineriais
template float generuotiGalvid<std::vector<float>>(const std::vector<float>&, int);

// Instancijavimas generuotiGalmed funkcijos su įvairiais konteineriais
template float generuotiGalmed<std::vector<float>>(const std::vector<float>&, int);

// Instancijavimas Studentas su įvairiais konteineriais
template class Studentas<std::vector<float>>;
template class Studentas<std::list<float>>;
template class Studentas<std::deque<float>>;

//template void Studentas<std::vector<float>>::rusiuotiStud(std::vector<Studentas<std::vector<float>>>&, char);
