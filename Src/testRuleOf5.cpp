#include "studentas.h"
#include "testRuleOf5.h"
#include <cassert>


// [TESTAS] Bandymas sukurti Zmogus objekta (turi nesikompiliuoti, jei atkomentuota)

//Zmogus z; //nesikompiliuoja, nes Zmogus yra abstrakti klase

// Šis testas rodo, kad Zmogus klase yra abstrakti – jos objektu sukurti negalima
// Bandant sukurti Zmogus z; gauname kompiliavimo klaida:
// “variable type 'Zmogus' is an abstract class”

void testuotiRuleOfFive() {
    // === 1. Originalus objektas ===
    cout << "\n[TEST 1] Originalaus objekto sukurimas\n";
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai({10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);
    cout << "Sukurtas s1: " << s1 << "\n";

    // === 2. Kopijavimo konstruktorius ===
    cout << "\n[TEST 2] Kopijavimo konstruktorius (s2 kopija is s1)\n";
    Studentas s2(s1);
    cout << "Kopijuotas s2: " << s2 << "\n";
    assert(s2.vardas() == s1.vardas());

    // === 3. Kopijavimo operatorius ===
    cout << "\n[TEST 3] Kopijavimo operatorius (s3 = s1)\n";
    Studentas s3;
    s3 = s1;
    cout << "Kopijuotas s3: " << s3 << "\n";
    assert(s3.pavarde() == s1.pavarde());

    // === 4. Perkelimo konstruktorius ===
    cout << "\n[TEST 4] Move konstruktorius (s4 = move(s1))\n";
    Studentas s4(move(s1));
    cout << "Perkeltas s4: " << s4 << "\n";
    assert(s4.egzaminas() == 9);

    // === 5. Perkelimo operatorius ===
    cout << "\n[TEST 5] Move operatorius (s5 = move(s2))\n";
    Studentas s5;
    s5 = move(s2);
    cout << "Perkeltas s5: " << s5 << "\n";
    assert(!s5.nd().empty());

    // === 6. Isvesties operatorius ===
    cout << "\n[TEST 6] Isvesties operatorius (<<)\n";
    ostringstream oss;
    oss << s5;
    cout << "Isvestas s5: " << oss.str() << "\n";
    assert(oss.str().find("Kopija") != string::npos);

    // === 7. Ivesties operatorius (istringstream) ===
    cout << "\n[TEST 7] Ivesties operatorius (>> is istringstream)\n";
    istringstream iss("Vardenis Pavardenis 10 10 10 10 10 10");
    Studentas s6;
    iss >> s6;
    cout << "Ivestas s6: " << s6 << "\n";
    assert(s6.vardas() == "Vardenis");

    // === 7.1 Ivestis is cin ===
    cout << "\n[TEST 7.1] Ivestis is cin (>>)\n";
    cout << "Iveskite:\n";
    Studentas s7;
    cin >> s7;
    cout << "Ivestas s7: " << s7 << "\n";
    assert(!s7.vardas().empty());

    // === 7.2 Ivestis is failo su operator>> ===
    cout << "\n[TEST 7.2] Ivestis is failo su operator>>\n";
    ofstream failin("failinis.txt");
    failin << "Antanas Antanaitis 9 8 7 6 5 7\n";
    failin.close();

    ifstream failIn("failinis.txt");
    Studentas s8;
    failIn >> s8;
    failIn.close();
    cout << "Is failo ivestas s8: " << s8 << "\n";
    assert(s8.vardas() == "Antanas");

    // === 7.3 Isvedimas i stringstream (<<) ===
    cout << "\n[TEST 7.3] Isvedimas i stringstream (<<)\n";
    ostringstream oss2;
    oss2 << s8;
    cout << "stringstream rezultatas: " << oss2.str() << "\n";
    assert(oss2.str().find("Antanaitis") != string::npos);

    // === 8. Failo nuskaitymas su Studentas::nuskaitymasFile ===
    cout << "\n[TEST 8] Failo nuskaitymas su nuskaitymasFile()\n";
    ofstream testFailas("studentai.txt");
    testFailas << "Jonas Jonaitis 10 9 8 7 6 8\n";
    testFailas << "Petras Petrauskas 8 9 7 10 5 7\n";
    testFailas.close();

    vector<Studentas> grupe;
    Studentas::nuskaitymasFile(grupe, "studentai.txt");
    cout << "Gauta studentu: " << grupe.size() << "\n";
    assert(grupe.size() == 2);
    assert(grupe[0].vardas() == "Jonas");
    assert(grupe[1].vardas() == "Petras");

    // === 9. Isvedimas i ekrana ir i faila ===
    cout << "\n[TEST 9] Isvedimas i ekrana ir i faila\n";

    // I ekrana
    cout << "Studentu rezultatai (ekrane):\n";
    for (const auto& s : grupe) cout << s << "\n";

    // I faila
    ofstream out("rezultataiT.txt");
    for (const auto& s : grupe) out << s << "\n";
    out.close();


    // === 10. Destruktoriaus testas ===
    cout << "\n[TEST 10] Destruktoriaus kvietimo testas\n";
    {
        Studentas laikinas;
    }
    cout << "Destruktoriaus kvietimu skaicius: " << Studentas::destruktoriuSk << "\n";

    cout << "\n Visi testai praejo sekmingai!\n\n";
}
