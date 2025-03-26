#include "studentas.h"

// Default konstruktorius
template <typename T>
Studentas<T>::Studentas() : egzaminas_(0), galutinis_balas_(0) {}

// Konstruktorius, kuris naudoja įvestį
template <typename T>
Studentas<T>::Studentas(std::istream& is) {
    readStudent(is);
}

// Galutinio balo skaičiavimas
template <typename T>
double Studentas<T>::galBalas(double (*balasFunkcija)(const T&)) const {
    return 0.4 * balasFunkcija(nd_) + 0.6 * egzaminas_;
}

// Nuskaitymo metodas iš stream'o
template <typename T>
std::istream& Studentas<T>::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;
    double pazymys;
    nd_.clear();  // Išvalome senus duomenis
    while (is >> pazymys) {
        nd_.push_back(pazymys);
    }
    return is;
}

// Set'eriai
template <typename T>
void Studentas<T>::setVardas(const std::string& v) {
    vardas_ = v;
}

template <typename T>
void Studentas<T>::setPavarde(const std::string& p) {
    pavarde_ = p;
}

template <typename T>
void Studentas<T>::setEgzaminas(int egz) {
    egzaminas_ = egz;
}

template <typename T>
void Studentas<T>::setNamudarbiai(const T& nd) {
    nd_ = nd;
}

// Funkcijos, susijusios su balų generavimu
template <typename T>
double generuotiGalvid(const T& nd, int egz) {
    double suma = 0;
    for (const auto& paz : nd) {
        suma += paz;
    }
    return 0.4 * (suma / nd.size()) + 0.6 * egz;
}

template <typename T>
double generuotiGalmed(const T& nd, int egz) {
    T sorted_nd = nd;
    std::sort(sorted_nd.begin(), sorted_nd.end());
    size_t kiek = sorted_nd.size();
    double mediana;

    if (kiek % 2 == 1) {
        mediana = sorted_nd[kiek / 2];
    } else {
        mediana = (sorted_nd[kiek / 2] + sorted_nd[kiek / 2 - 1]) / 2.0;
    }
    return 0.4 * mediana + 0.6 * egz;
}

// Nuskaitymo funkcija
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
        ss >> laik.vardas() >> laik.pavarde();

        double pazymys;
        laik.nd().clear();
        while (ss >> pazymys) {
            laik.nd().push_back(pazymys);
        }

        grupe.push_back(laik);
    }
}

// Rezultatų spausdinimas į ekraną
template <typename T>
void Studentas<T>::spausdintiRez(std::vector<Studentas<T>>& grupe, bool iFaila, char pasirinkimas, const std::string& failoPavadinimas) {
    for (auto& stud : grupe) {
        stud.galBalas(generuotiGalvid);
    }

    if (iFaila) {
        std::ofstream failas(failoPavadinimas);
        if (!failas) {
            std::cerr << "Nepavyko atidaryti failo rezultatams.\n";
            return;
        }

        for (const auto& stud : grupe) {
            failas << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
        }

        std::cout << "Rezultatai išsaugoti faile " << failoPavadinimas << std::endl;
    } else {
        for (const auto& stud : grupe) {
            std::cout << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
        }
    }
}

// Rūšiavimo funkcija
template <typename T>
void Studentas<T>::rusiuotiStud(std::vector<Studentas<T>>& grupe, char rusiavimoPas) {
    if (rusiavimoPas == 'v') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { 
            return a.vardas() < b.vardas(); 
        });
    } else if (rusiavimoPas == 'p') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { 
            return a.pavarde() < b.pavarde(); 
        });
    } else if (rusiavimoPas == 'g') {
        std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { 
            return a.galutinisBalsas() > b.galutinisBalsas(); 
        });
    }
}

// Explicit instanciacija dėl šablonų
template class Studentas<std::vector<double>>;
template class Studentas<std::list<double>>;
template class Studentas<std::deque<double>>;
