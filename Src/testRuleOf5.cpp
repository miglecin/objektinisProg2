#include "studentas.h"
#include "testRuleOf5.h"
#include <cassert>

void testuotiRuleOfFive() {

    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);

    // Copy konstruktorius
    Studentas s2(s1);
    assert(s2.vardas() == s1.vardas());

    // Copy operatorius
    Studentas s3;
    s3 = s1;
    assert(s3.pavarde() == s1.pavarde());

    // Move konstruktorius
    Studentas s4(std::move(s1));
    assert(s4.egzaminas() == 9);

    // Move operatorius
    Studentas s5;
    s5 = std::move(s2);
    assert(!s5.nd().empty());

    // Stream operatoriai
    std::ostringstream oss;
    oss << s5;
    assert(oss.str().find("Kopija") != std::string::npos);

    std::istringstream iss("Vardenis Pavardenis 10 10 10 10 10 10");
    Studentas s6;
    iss >> s6;
    assert(s6.vardas() == "Vardenis");

    cout << "\nDestruktoriaus iškvietimų skaičius\n";
    {
        Studentas laikinas;
    } 
    cout << " Destruktoriaus kvietimų skaičius (iki šiol): " << Studentas::destruktoriuSk << '\n';

    cout << "\n Visi Rule of Five + IO operatorių testai praėjo sėkmingai!\n\n";
}
