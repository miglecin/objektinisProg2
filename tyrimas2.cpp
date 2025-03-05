#include "tyrimas2.h"
#include "sufailais.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"

void testuotiDuomenuApdorojima(int skaicius, const std::string& aplankas, const std::string& rezultataiAplankas) {
    // Laiko matavimas visai programai
    LaikoMatavimas visoLaikoMatavimas("Visos programos laikas");
    visoLaikoMatavimas.pradeti();

    vector<studentas> grupe;

    // Laiko matavimas failo nuskaitymui
    LaikoMatavimas laikoMatavimasNuskaitymui("Failo nuskaitymas");
    laikoMatavimasNuskaitymui.pradeti();
    nuskaitymasFile(grupe, aplankas + "/studentai_" + std::to_string(skaicius) + ".txt");
    laikoMatavimasNuskaitymui.baigti();

    char pasirinkimas;
    cout << "Koki metoda renkates gal. balui skaiciuoti?\n";
    cout << " [v] - vidurkį\n [m] - medianą\n";
    cin >> pasirinkimas;
    while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
    }

    // Skaičiuojame galutinį balą pagal pasirinkimą
    for (auto& stud : grupe) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    // Laiko matavimas studentų rūšiavimui į dvi grupes
    LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
    laikoMatavimasRusiavimui.pradeti();

    vector<studentas> vargsiai, kietiakai;
    for (auto& stud : grupe) {
        if (stud.Gal < 5.0) {
            vargsiai.push_back(stud);
        } else {
            kietiakai.push_back(stud);
        }
    }

    laikoMatavimasRusiavimui.baigti();

    // Laiko matavimas vargšų rezultatų išvedimui
    LaikoMatavimas laikoMatavimasIsvedimuiVargsai("Vargšų rezultatų išvedimas");
    laikoMatavimasIsvedimuiVargsai.pradeti();

    string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + std::to_string(skaicius) + ".txt";
    spausdintiRez(vargsiai, true, pasirinkimas, vargsiuFailas);

    laikoMatavimasIsvedimuiVargsai.baigti();

    // Laiko matavimas kietiakų rezultatų išvedimui
    LaikoMatavimas laikoMatavimasIsvedimuiKietiakai("Kietiakų rezultatų išvedimas");
    laikoMatavimasIsvedimuiKietiakai.pradeti();

    string kietiakuFailas = rezultataiAplankas + "/kietiakiai_" + std::to_string(skaicius) + ".txt";
    spausdintiRez(kietiakai, true, pasirinkimas, kietiakuFailas);

    laikoMatavimasIsvedimuiKietiakai.baigti();

    cout << "Studentai išskaidyti į 2 failus: " << vargsiuFailas << " ir " << kietiakuFailas << endl;

    // Laiko matavimas visai programai pabaigti
    visoLaikoMatavimas.baigti();
}
