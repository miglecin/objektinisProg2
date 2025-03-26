#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>

// Pagrindinė Studentas klasė su šablonais
template <typename T = std::vector<double>>  // T gali būti bet koks konteineris (vector, list, deque)
class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    int egzaminas_;
    T nd_;  // Namų darbų konteineris (T gali būti vector, list, deque)
    double galutinis_balas_;

public:
    // Konstruktoriai
    Studentas();  // Default konstruktorius
    Studentas(std::istream& is);  // Konstruktorius su įvestimi

    // Get'eriai
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline int egzaminas() const { return egzaminas_; }
    inline const T& nd() const { return nd_; }
    inline double galutinisBalsas() const { return galutinis_balas_; }

    // Nustatymo metodai
    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
    void setEgzaminas(int e);
    void setNamudarbai(const T& nd);

    // Galutinio balo metodas
    double galBalas(double (*balasFunkcija)(const T&) = generuotiGalvid) const;

    // Nuskaitymo metodas
    std::istream& readStudent(std::istream&);

    // Rūšiavimo metodas pagal įvairius kriterijus
    static void rusiuotiStud(std::vector<Studentas<T>>& grupe, char rusiavimoPas);

    // Nuskaitymo funkcija
    static void nuskaitymasFile(std::vector<Studentas<T>>& grupe, const std::string& filename);

    // Rezultatų spausdinimas į ekraną
    static void spausdintiRez(std::vector<Studentas<T>>& grupe, bool iFaila, char pasirinkimas, const std::string& failoPavadinimas);
};

// Funkcijos, susijusios su balų generavimu
template <typename T>
double generuotiGalvid(const T& nd, int egz);

template <typename T>
double generuotiGalmed(const T& nd, int egz);

#endif
