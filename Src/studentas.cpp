#include "studentas.h"

// Konstruktoriaus realizacija
Studentas::Studentas() : egzaminas_(0), galutinis_balas_(0) {}

Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

// Funkcija, kuri nuskaito studento duomenis iš srauto
std::istream& Studentas::readStudent(std::istream& is) {
    is>>vardas_>>pavarde_; 
    float ndTemp;
    nd_.clear();
    for (int i = 0; i < 5; ++i) {
        is >> ndTemp;
        nd_.push_back(ndTemp);
    }
    is >> egzaminas_;
    return is;
}

// Galutinio balo skaičiavimas pagal vidurkį
float generuotiGalvid(const std::vector<float>& nd, int egz) {
    float suma = std::accumulate(nd.begin(), nd.end(), 0.0f);
    float vidurkis = suma / nd.size();
    return 0.4f * vidurkis + 0.6f * egz;
}

// Galutinio balo skaičiavimas pagal medianą
float generuotiGalmed(const std::vector<float>& nd, int egz) {
    std::vector<float> sorted(nd.begin(), nd.end());
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    float mediana = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    return 0.4f * mediana + 0.6f * egz;
}

// Galutinio balo funkcija, kur galima naudoti pasirinktinę funkciją
float Studentas::galBalas(float (*balasFunkcija)(const std::vector<float>&, int)) {
    
    // Apskaičiuojame galutinį balą pagal pasirinktą funkciją
    galutinis_balas_ = balasFunkcija(nd_, egzaminas_);  // Teisingas priskyrimas
    
    return galutinis_balas_;  // Grąžiname užrašytą galutinį balą
}
// Studentų rūšiavimas
void Studentas::rusiuotiStud(std::vector<Studentas>& grupe, char rusiavimoPas) {
    if (rusiavimoPas == 'v') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas_ < b.vardas_;
        });
    } else if (rusiavimoPas == 'p') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde_ < b.pavarde_;
        });
    } else if (rusiavimoPas == 'g') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisBalsas() > b.galutinisBalsas();
        });
    }
}

// Nuskaitymas iš failo
void Studentas::nuskaitymasFile(std::vector<Studentas>& grupe, const std::string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::string eilute;
    getline(failas, eilute);  // praleidžiame pirmą eilutę (antraštę)

    Studentas laik;
    while (getline(failas, eilute)) {
        std::istringstream ss(eilute);
        if (ss) {
            laik.readStudent(ss);
            grupe.push_back(laik);
        } else {
            std::cerr << "Klaida nuskaityti eilutę: " << eilute << std::endl;
        }
    }

    failas.close();
}
