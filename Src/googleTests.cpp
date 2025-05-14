#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp" 
#include "studentas.h"
#include <sstream>
#include <fstream>
#include <cmath>

TEST_CASE("Studentas klasės testai") {
    

    SECTION("Konstruktoriai ir operatoriai") {
        // 1st test: Default konstruktorius
        SECTION("Default konstruktorius") {
            Studentas s;
            s.setVardas("Base");
            s.setPavarde("Student");
            s.setEgzaminas(8);
            s.setNamudarbai({9, 8, 7});

            REQUIRE(s.vardas() =="Base");
            REQUIRE(s.pavarde()=="Student");
            REQUIRE(s.egzaminas() == 8);
        }

        // 2nd test: Kopijavimo konstruktorius
        SECTION("Kopijavimo konstruktorius") {
            Studentas s_original;
            s_original.setVardas("Base");
            s_original.setPavarde("Student");
            Studentas copy(s_original);

            REQUIRE(copy.vardas() == "Base");
            REQUIRE(copy.pavarde() == "Student");
        }

        // 3rd test: Kopijavimo operatorius

        // 4th test: Perkėlimo konstruktorius
        SECTION("Perkelimo konstruktorius") {
            Studentas s_source;
            s_source.setVardas("Base");
            s_source.setPavarde("Student");
            Studentas s_move(std::move(s_source));

            REQUIRE(s_move.vardas() == "Base");
            REQUIRE(s_move.pavarde() == "Student");
            REQUIRE(s_source.vardas().empty());
    }
    }

    SECTION("Operatoriai") {
         // 3rd test: Kopijavimo operatorius
        SECTION("Kopijavimo operatorius") {
        Studentas s_original;
        s_original.setVardas("testas");
        s_original.setPavarde("testukas");
        Studentas s_copy;
        s_copy = s_original;
        
        REQUIRE(s_copy.vardas() == "testas");
        REQUIRE(s_copy.pavarde() == "testukas");
    }

     // 5th test: Perkėlimo operatorius
        SECTION("Perkėlimo operatorius") {
        Studentas s_source;
        s_source.setVardas("testas");
        s_source.setPavarde("testukas");
        Studentas s_move;
        s_move = std::move(s_source);

        REQUIRE(s_move.vardas() == "testas");
        REQUIRE(s_move.pavarde() == "testukas");
        REQUIRE(s_source.vardas().empty());
    }

    SECTION("Stream operatoriai") {
        SECTION("Išvesties operatorius") {
            std::ostringstream oss;
             Studentas s;
             s.setVardas("Student");
            s.setPavarde("testukas");
            s.setNamudarbai({1, 2, 3, 4, 5});
            s.setEgzaminas(10);
            oss << s;
            REQUIRE(oss.str().find("Student") != std::string::npos);
        }

        SECTION("Įvesties operatorius") {
            std::istringstream iss("Naujas Studentas 10 9 9 8 8 7");
            Studentas s;
            iss >> s;
            REQUIRE(s.vardas() == "Naujas");
            REQUIRE(s.pavarde() == "Studentas");
            REQUIRE(s.egzaminas() == 7);
        }
    }

    SECTION("Failų operacijos") {
        SECTION("Nuskaitymas iš failo") {
    const std::string failoVardas = "test_studentai.txt";
    {
        std::ofstream out(failoVardas);
        out << "Jonas Jonaitis 10 9 8 7 6 5\n"; 
        out << "Petras Petraitis 7 6 5 4 3 2\n";
    }

            std::vector<Studentas> grupe;
            Studentas::nuskaitymasFile(grupe, "test_studentai.txt");
            REQUIRE(grupe.size() == 2);  
            REQUIRE(grupe[0].vardas() == "Jonas");
            REQUIRE(grupe[0].pavarde() == "Jonaitis");
            REQUIRE(grupe[0].nd() == std::vector<float>({10, 9, 8, 7, 6}));
            REQUIRE(grupe[0].egzaminas() == 5);
        }

        SECTION("Įrašymas į failą") {
        Studentas s;
        s.setVardas("Base");
        s.setPavarde("testukas");
        s.setNamudarbai({1, 2, 3, 4, 5});
        s.setEgzaminas(10);
            std::string filename = "test_irasymas.txt";
            std::ofstream out(filename);
            out << s;
            out.close();

            std::ifstream in(filename);

            in >> s;
            REQUIRE(s.vardas() == "Base");
        }
    }

    SECTION("Destruktoriaus testas") {
        int initialCount = Studentas::destruktoriuSk;
        {
            Studentas temp;
        }
        REQUIRE(Studentas::destruktoriuSk == initialCount + 1);
    }
}
}

TEST_CASE("Galutinio balo funkcijos") {
    SECTION("Generuojamas galutinis balas pagal vidurkį") {
        std::vector<float> nd = {9, 8, 7, 6, 10};  // Namu darbu pazymiai
        int egz = 8;  // Egzamino pazymys
        
        float galutinis = generuotiGalvid(nd, egz);  // Skaičiuojame galutinį balą
        
        // Skaičiuojame vidurkį
        float vidurkis = std::accumulate(nd.begin(), nd.end(), 0.0f) / nd.size();  
        
        // Tikėtinas rezultatas pagal formulę
        float expected = 0.4f * vidurkis + 0.6f * egz;  
        
        // Patikriname, kad galutinis balas yra pakankamai artimas tikėtinam rezultatui
        REQUIRE(std::abs(galutinis - expected) < 0.01f);  // Patikriname su paklaida
    }

    SECTION("Generuojamas galutinis balas pagal medianą") {
        std::vector<float> nd = {9, 8, 7, 6, 10};  // Namu darbu pazymiai
        int egz = 8;  // Egzamino pazymys
        
        float galutinis = generuotiGalmed(nd, egz);  // Skaičiuojame galutinį balą
        
        std::vector<float> sorted(nd);
        std::sort(sorted.begin(), sorted.end());  // Rūšiuojame namų darbų pažymius
        
        // Apskaičiuojame medianą
        float mediana = (sorted.size() % 2 == 0) ?
            (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2 :
            sorted[sorted.size() / 2];  // Mediana
        
        float expected = 0.4f * mediana + 0.6f * egz;  
        
        REQUIRE(std::abs(galutinis - expected) < 0.01f); 
    }

    SECTION("Testuojame tuščius namų darbus") {
    std::vector<float> nd = {};  // Namu darbu pazymiai (tuščias)
    int egz = 10;  // Egzamino pazymys

    float galutinis = generuotiGalvid(nd, egz);  
    REQUIRE(std::isnan(galutinis)); 
    }
}
