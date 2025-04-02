#include "studentas.h"

//default konstruktoriaus realizacija
Studentas::Studentas() : egzaminas_(0), galutinis_balas_(0) {}

Studentas::Studentas(std::istream& is) {
    readStudent(is);
}


// Funkcija, kuri nuskaito studento duomenis iš srauto
std::istream& Studentas::readStudent(std::istream& is) {
    is>>vardas_>>pavarde_; 
    float ndTemp;
    nd_.clear(); //isvalomas senas nd vektorius
    for (int i = 0; i < 5; ++i) {
        is >> ndTemp;
        nd_.push_back(ndTemp);
    }
    is >> egzaminas_;
    return is;
}

//galutinio balo skaičiavimas pagal vidurkį
float generuotiGalvid(const vector<float>& nd, int egz) {
    float suma = std::accumulate(nd.begin(), nd.end(), 0.0f);
    float vidurkis = suma / nd.size();
    return 0.4f * vidurkis + 0.6f * egz;
}

//galutinio balo skaičiavimas pagal medianą
float generuotiGalmed(const vector<float>& nd, int egz) {
    vector<float> sorted(nd.begin(), nd.end());
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.size();
    float mediana = (size % 2 == 0) ? (sorted[size / 2 - 1] + sorted[size / 2]) / 2 : sorted[size / 2];
    return 0.4f * mediana + 0.6f * egz;
}

//galutinio balo funkcija, kur galima naudoti pasirinktinę funkciją
float Studentas::galBalas(float (*balasFunkcija)(const vector<float>&, int)) {
    
    //apskaiciuojme gal bala
    galutinis_balas_= balasFunkcija(nd_, egzaminas_);  
    
    return galutinis_balas_;  //graziname galutinį balą
}
//Studentu rusiavimas
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

//nuskaitymas iš failo
void Studentas::nuskaitymasFile(vector<Studentas>& grupe, const string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    string eilute;
    getline(failas, eilute);  // praleidžiame pirmą eilutę (antraštę)

    Studentas laik;
    while (getline(failas, eilute)) {
        std::istringstream ss(eilute);
        if (ss) {
            laik.readStudent(ss);
            grupe.push_back(laik);
        } else {
            cerr << "Klaida nuskaityti eilutę: " << eilute <<endl;
        }
    }

    failas.close();
}
