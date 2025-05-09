#define CATCH_CONFIG_NOMAIN 
#include "catch_amalgamated.hpp"
#include "studentas.h"
#include <sstream>
#include <fstream>

// [TESTAS] Bandymas sukurti Zmogus objekta (turi nesikompiliuoti, jei atkomentuota)

// Zmogus z; // nesikompiliuoja, nes Zmogus yra abstrakti klase
// Šis testas rodo, kad Zmogus klase yra abstrakti – jos objektu sukurti negalima
// Bandant sukurti Zmogus z; gauname kompiliavimo klaida:
// “variable type 'Zmogus' is an abstract class”

// === 1. Originalus objektas ===
TEST_CASE("Default constructor test") {
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);
    std::cout << "Sukurtas studentas: " << s1.vardas() << " " << s1.pavarde() << "\n";

    REQUIRE(s1.vardas() == "Testas");
    REQUIRE(s1.pavarde() == "Kopija");
    REQUIRE(s1.egzaminas() == 9);
}

// === 2. Kopijavimo konstruktorius ===
TEST_CASE("Copy constructor test") {
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);

    Studentas s2(s1);
    std::cout << "Kopijuotas s2: " << s2 << "\n";

    REQUIRE(s2.vardas() == s1.vardas());
    REQUIRE(s2.pavarde() == s1.pavarde());
}

// === 3. Kopijavimo operatorius ===
TEST_CASE("Copy assignment operator test") {
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);

    Studentas s3;
    s3 = s1;
    std::cout << "Kopijuotas s3: " << s3 << "\n";

    REQUIRE(s3.pavarde() == s1.pavarde());
}

// === 4. Perkelimo konstruktorius ===
TEST_CASE("Move constructor test") {
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);

    Studentas s4(std::move(s1));
    std::cout << "Perkeltas s4: " << s4 << "\n";

    REQUIRE(s4.egzaminas() == 9);
}

// === 5. Perkelimo operatorius ===
TEST_CASE("Move assignment operator test") {
    Studentas s2;
    s2.setVardas("Testas");
    s2.setPavarde("Kopija");
    s2.setEgzaminas(9);
    s2.setNamudarbai({10, 9, 8, 7, 6});
    s2.galBalas(generuotiGalvid);

    Studentas s5;
    s5 = std::move(s2);
    std::cout << "Perkeltas s5: " << s5 << "\n";

    REQUIRE_FALSE(s5.nd().empty());
}

// === 6. Isvesties operatorius ===
TEST_CASE("Stream insertion operator test") {
    Studentas s5;
    s5.setVardas("Jonas");
    s5.setPavarde("Petras");
    s5.setEgzaminas(9);
    s5.setNamudarbai({10, 9, 8, 7, 6});
    s5.galBalas(generuotiGalvid);

    std::ostringstream oss;
    oss << s5;
    std::cout << "Isvestas s5: " << oss.str() << "\n";

    REQUIRE(oss.str().find("Petras") != std::string::npos);
}

// === 7. Ivesties operatorius (istringstream) ===
TEST_CASE("Stream extraction operator test") {
    std::istringstream iss("Vardenis Pavardenis 10 10 10 10 10 10");
    Studentas s6;
    iss >> s6;
    std::cout << "Ivestas s6: " << s6 << "\n";

    REQUIRE(s6.vardas() == "Vardenis");
}

// === 8. Failo nuskaitymas su Studentas::nuskaitymasFile ===
TEST_CASE("File input test") {
    std::ofstream testFailas("studentai.txt");
    testFailas << "Jonas Jonaitis 10 9 8 7 6 8\n";
    testFailas << "Petras Petrauskas 8 9 7 10 5 7\n";
    testFailas.close();

    std::vector<Studentas> grupe;
    Studentas::nuskaitymasFile(grupe, "studentai.txt");
    std::cout << "Gauta studentu: " << grupe.size() << "\n";

    REQUIRE(grupe.size() == 2);
    REQUIRE(grupe[0].vardas() == "Jonas");
    REQUIRE(grupe[1].vardas() == "Petras");
}

// === 9. Isvedimas i ekrana ir i faila ===
TEST_CASE("Output to file test") {
    std::ofstream out("rezultataiT.txt");
    Studentas s1;
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    out << s1 << "\n";
    out.close();

    std::ifstream in("rezultataiT.txt");
    Studentas s2;
    in >> s2;
    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.pavarde() == "Jonaitis");
}

// === 10. Destruktoriaus testas ===
TEST_CASE("Destructor test") {
    {
        Studentas laikinas;
    }
    // Patikrinkite, ar destruktorius buvo iškviestas (pagal skaitiklį arba kitą metodą)
    REQUIRE(Studentas::destruktoriuSk == 1);
}