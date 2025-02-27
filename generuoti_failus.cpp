#include "studentas.h"
#include "generuoti_failus.h"

namespace fs=std::filesystem;

void generuotiFaila(int skaicius, const string& aplankas) {
    //sukuria aplanka jei neegzistuoja
    if (!fs::exists(aplankas)) {
        fs::create_directory(aplankas);
    }

    //sukuria faila su generuojamu pavadinimu
    string failoPavadinimas=aplankas + "/studentai_" + std::to_string(skaicius) + ".txt";
    ofstream failas(failoPavadinimas);
    
    if (!failas) 
    {
        cerr<<"Nepavyko sukurti failo: "<<failoPavadinimas<<endl;
        return;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> pazymysDist(1, 10); //paz nuo 1 iki 10
    std::uniform_int_distribution<int> vardasNrDist(1, 10000); //vardu nr

    //generuoja studentu sarasa
    for (int i=0; i<skaicius; ++i) {
        ostringstream vardas;
        vardas<< "Vardas"<<vardasNrDist(mt);
        
        ostringstream pavarde;
        pavarde<<"Pavarde"<<vardasNrDist(mt);

        //generuoja paz
        vector<int> pazymiai;
        for (int j=0; j<5; ++j) 
        {
            pazymiai.push_back(pazymysDist(mt)); //generuojam 5 random paz
        }

        //egz
        int egzaminas=pazymysDist(mt);

        //rasom i faila
        failas<<vardas.str()<< " " <<pavarde.str(); 
        for (const auto& paz : pazymiai) {
            failas<< " "<<paz;
        }
        failas<< " " <<egzaminas<<endl;
    }

    failas.close();
   cout<<"Sugeneruotas failas: "<<failoPavadinimas<<endl;
}
