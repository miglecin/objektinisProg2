#include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"
#include "generuoti_failus.h"

int main() {
    string aplankas="test_files"; //aplankas, kur saugomi sugeneruoti failai
    string rezultataiAplankas="rezultatai"; //aplankas kur saugomi rezultatai

      //sukuriame aplanka 'rezultatai', jei jis neegzistuoja
      if (!std::filesystem::exists(rezultataiAplankas)) 
      {
        std::filesystem::create_directory(rezultataiAplankas);
      }

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
           cout<< "Neteisingas pasirinkimas"<<endl;
            return 1;
    }


    //Laiko matavimas failo kurimui
    LaikoMatavimas laikoMatavimasGeneravimas("Failo kūrimas");
    laikoMatavimasGeneravimas.pradeti();
    generuotiFaila(skaicius, aplankas); //Sugeneruoti faila su studentu duom
    laikoMatavimasGeneravimas.baigti();

    vector<studentas> grupe;
    nuskaitymasFile(grupe, aplankas + "/studentai_" + std::to_string(skaicius) + ".txt"); //nuskaityti studentus is sugeneruoto failo
    

    char pasirinkimas;
    cout << "Koki metoda renkates gal. balui skaiciuoti?\n";
    cout << " [v] - vidurki\n [m] - mediana\n";
    cin >> pasirinkimas;
    while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
    }

    //galutinis balas pagal pasirinkima
    for (auto& stud : grupe) {
        stud.Gal=pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }


    rusiuotiStud(grupe, 'g');  //surusiuoti (kietiakai-pirmiausiai, vargsai-veliau)
    

    /*LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
    laikoMatavimasRusiavimui.pradeti();*/
    //i dvi grupes
    vector<studentas> vargsiai, kietiakai;
    
    //pagal galutini bala
    for (auto& stud : grupe) {
        if (stud.Gal<5.0) {
            vargsiai.push_back(stud); 
        } else {
            kietiakai.push_back(stud); 
        }
    }
    //laikoMatavimasRusiavimui.baigti();

    //isveda vargsus
    string vargsiuFailas=rezultataiAplankas + "/vargsiai_" + std::to_string(skaicius) + ".txt";
    spausdintiRez(vargsiai, true, pasirinkimas, vargsiuFailas);
    

    //isveda kietiakus
    string kietiakuFailas=rezultataiAplankas + "/kietiakiai_" + std::to_string(skaicius) + ".txt";
    spausdintiRez(kietiakai, true, pasirinkimas, kietiakuFailas);
    
    cout<<"Studentai iskaidyti i 2 failus: "<<vargsiuFailas<<" ir "<<kietiakuFailas<<endl;

    return 0;
}
