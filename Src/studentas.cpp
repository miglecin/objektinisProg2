#include "studentas.h"

// Konstruktoriai
Studentas::Studentas() : egzaminas_(0), galutinis_balas_(0.0f) {}

Studentas::Studentas(istream& is) {
    readStudent(is);
}

//Rule of Five
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      egzaminas_(other.egzaminas_), nd_(other.nd_),
      galutinis_balas_(other.galutinis_balas_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        egzaminas_ = other.egzaminas_;
        nd_ = other.nd_;
        galutinis_balas_ = other.galutinis_balas_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)),
      egzaminas_(other.egzaminas_), nd_(std::move(other.nd_)),
      galutinis_balas_(other.galutinis_balas_) {
    other.egzaminas_ = 0;
    other.galutinis_balas_ = 0.0f;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        egzaminas_ = other.egzaminas_;
        nd_ = std::move(other.nd_);
        galutinis_balas_ = other.galutinis_balas_;

        other.egzaminas_ = 0;
        other.galutinis_balas_ = 0.0f;
    }
    return *this;
}
int Studentas::destruktoriuSk = 0;

// Getteriai ir Setteriai
void Studentas::setVardas(const string& v) { vardas_ = v; }
void Studentas::setPavarde(const string& p) { pavarde_ = p; }
void Studentas::setEgzaminas(int e) { egzaminas_ = e; }
void Studentas::setNamudarbai(const vector<float>& nd) { nd_ = nd; }

// Galutinio balo skaičiavimas
float Studentas::galBalas(float (*balasFunkcija)(const vector<float>&, int)) {
    galutinis_balas_ = balasFunkcija(nd_, egzaminas_);
    return galutinis_balas_;
}

// Įvestis iš srauto
istream& Studentas::readStudent(istream& is) {
    is >> vardas_ >> pavarde_;
    float ndTemp;
    nd_.clear();
    for (int i = 0; i < 5; ++i) {
        is >> ndTemp;
        nd_.push_back(ndTemp);
    }
    is >> egzaminas_;
    return is;
}

// Stream operatoriai
ostream& operator<<(ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vardas_
       << std::setw(15) << s.pavarde_
       << std::setw(10) << s.egzaminas_
       << std::fixed << std::setprecision(2)
       << std::setw(10) << s.galutinis_balas_;
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    return s.readStudent(is);
}

// Rūšiavimas
void Studentas::rusiuotiStud(vector<Studentas>& grupe, char rusiavimoPas) {
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

// Failo nuskaitymas
void Studentas::nuskaitymasFile(vector<Studentas>& grupe, const string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    string eilute;
    std::getline(failas, eilute);  // praleidžiame antraštę

    Studentas laik;
    while (std::getline(failas, eilute)) {
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

// Galutinio balo funkcijos
float generuotiGalvid(const vector<float>& nd, int egz) {
    float suma = std::accumulate(nd.begin(), nd.end(), 0.0f);
    float vidurkis = suma / nd.size();
    return 0.4f * vidurkis + 0.6f * egz;
}

float generuotiGalmed(const vector<float>& nd, int egz) {
    vector<float> sorted(nd);
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    float mediana = (size % 2 == 0) ?
        (sorted[size / 2 - 1] + sorted[size / 2]) / 2 :
        sorted[size / 2];
    return 0.4f * mediana + 0.6f * egz;
}

Studentas::~Studentas() {
    ++destruktoriuSk;
    nd_.clear();  // (gali ir nereikėti, bet jei nori palikt – ok)
    std::cout << "[DESTRUKTORIUS] Išsikvietė. Iš viso: " << destruktoriuSk << "\n";
}
