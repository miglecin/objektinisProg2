#include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"
#include "generuoti_failus.h"

int main() {
    string aplankas = "test_files"; // Nurodykite norimą aplanką, kurioje bus saugomi failai
    
    int skaicius;
    int pasirinktasDydis;
    cout << "Pasirinkite failo dydį:\n";
    cout << "1 - 1000 studentų\n";
    cout << "2 - 10000 studentų\n";
    cout << "3 - 100000 studentų\n";
    cout << "4 - 1000000 studentų\n";
    cout << "5 - 10000000 studentų\n";
    cout << "Pasirinkimas: ";
    cin >> pasirinktasDydis;

    switch (pasirinktasDydis) {
        case 1:
            skaicius = 1000;
            break;
        case 2:
            skaicius = 10000;
            break;
        case 3:
            skaicius = 100000;
            break;
        case 4:
            skaicius = 1000000;
            break;
        case 5:
            skaicius = 10000000;
            break;
        default:
            std::cout << "Neteisingas pasirinkimas. Baigiamas darbas." << std::endl;
            return 1;
    }

    generuotiFaila(skaicius, aplankas); // Sugeneruoti failą su studentų duomenimis
    vector<studentas> grupe;
    nuskaitymasFile(grupe, aplankas + "/studentai_" + to_string(skaicius) + ".txt"); // Nuskaityti studentus iš sugeneruoto failo
    
    // Vartotojo pasirinkimas dėl galutinio balo skaičiavimo
    char pasirinkimas;
    cout << "Koki metoda renkates gal. balui skaiciuoti?\n";
    cout << " [v] - vidurki\n [m] - mediana\n";
    cin >> pasirinkimas;
    while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
    }

    // Skaičiuojame galutinį balą pagal pasirinkimą
    for (auto& stud : grupe) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    // Rūšiuojame studentus pagal galutinį balą
    rusiuotiStud(grupe, 'g');  // Studentus rūšiuos pagal galutinį balą (kietiakiai - pirmiausiai, vargšai - vėliau)
    
    // Skirstome studentus į dvi grupes
    vector<studentas> vargsiai, kietiakiai;
    
    // Suskirstome studentus pagal galutinį balą
    for (auto& stud : grupe) {
        if (stud.Gal < 5.0) {
            vargsiai.push_back(stud); // Studentai, kurių galutinis balas mažesnis nei 5
        } else {
            kietiakiai.push_back(stud); // Studentai, kurių galutinis balas 5 ar daugiau
        }
    }
    
    // Išvedame vargšus į failą
    string vargsiuFailas = aplankas + "/vargsiai_" + to_string(skaicius) + ".txt";
    spausdintiRez(vargsiai, true, pasirinkimas, 'g', vargsiuFailas);
    
    // Išvedame kietiakus į failą
    string kietiakiuFailas = aplankas + "/kietiakiai_" + to_string(skaicius) + ".txt";
    spausdintiRez(kietiakiai, true, pasirinkimas, 'g', kietiakiuFailas);
    
    cout << "Studentai išskaidyti į 2 failus: " << vargsiuFailas << " ir " << kietiakiuFailas << endl;

    return 0;
}
