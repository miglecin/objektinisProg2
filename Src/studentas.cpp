#include "studentas.h"

// Konstruktoriai
Studentas::Studentas() : egzaminas_(0), galutinis_balas_(0.0f) {}

Studentas::Studentas(istream& is) {
    readStudent(is);
}

// Rule of Five
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
    galutinis_balas_ = generuotiGalvid(nd_, egzaminas_);
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
    if (&is == &std::cin) {
        // INTERAKTYVUS ĮVEDIMAS
        std::string vardas, pavarde;
        std::vector<float> nd;
        float paz;
        int egzaminas;

        std::cout << "Studento vardas: ";
        is >> vardas;

        std::cout << "Studento pavardė: ";
        is >> pavarde;

        std::cout << "Namu darbu pazymiai (iveskite po viena, ENTER uzbaigia): ";
        while (true) {
            is >> paz;

            if (is.fail()) {
                std::cout << "✘ Netinkama įvestis. Įveskite pažymį nuo 1 iki 10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (paz < 1 || paz > 10) {
                std::cout << "✘ Pažymys turi būti nuo 1 iki 10: ";
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            nd.push_back(paz);
            if (is.peek() == '\n') break;
        }

        std::cout << "Egzamino pažymys: ";
        while (true) {
            is >> egzaminas;
            if (is.fail() || egzaminas < 1 || egzaminas > 10) {
                std::cout << "✘ Egzaminas turi būti nuo 1 iki 10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        s.setVardas(vardas);
        s.setPavarde(pavarde);
        s.setNamudarbai(nd);
        s.setEgzaminas(egzaminas);
        s.galBalas(generuotiGalvid);

    } else {
        // TYLUS AUTOMATINIS ĮVEDIMAS
        return s.readStudent(is);  // Naudoja tavo esamą metodą
    }

    return is;
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

    Studentas laik;
    while (std::getline(failas, eilute)) {
        std::istringstream ss(eilute);

        // Tikriname, ar srautas sėkmingai nuskaito visus laukus
        std::string vardas, pavarde;
        int egzaminas;
        std::vector<float> nd(5);

        if (ss >> vardas >> pavarde >> nd[0] >> nd[1] >> nd[2] >> nd[3] >> nd[4] >> egzaminas) {
            laik.setVardas(vardas);
            laik.setPavarde(pavarde);
            laik.setNamudarbai(nd);
            laik.setEgzaminas(egzaminas);
            laik.galBalas(generuotiGalvid); 
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
    nd_.clear();
    std::cout << "[DESTRUKTORIUS] Išsikvietė. Iš viso: " << destruktoriuSk << "\n";
}
