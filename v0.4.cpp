#include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"
#include "generuoti_failus.h"
#include "tyrimas1.h"
#include "tyrimas2.h"

int main() {
    string aplankas="test_files"; //aplankas, kur saugomi sugeneruoti failai
    string rezultataiAplankas = "rezultatai"; //Aplankas kur saugomi rezultatai

      //sukuriame aplanka 'rezultatai', jei jis neegzistuoja
      if (!std::filesystem::exists(rezultataiAplankas)) 
      {
        std::filesystem::create_directory(rezultataiAplankas);
      }

    /*int skaicius;
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
    }*/


    //laiko matavimas failo kūrimui
    //testuotiFailoGeneravima(skaicius, aplankas);

    int skaicius=10000000;
    //laiko matavimas 2 tyrimui
    testuotiDuomenuApdorojima(skaicius, aplankas, rezultataiAplankas);

    return 0;
}
