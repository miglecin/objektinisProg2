#include "rikiavimas.h"
#include "sufailais.h"


void nuskaitymasFile(vector<studentas>&grupe, const string& filename)
{
    ifstream failas(filename);
    if (!failas) //patikrinam ar atsidare failas
    {
        cerr<<"nepavyko atidaryti failo!"<<filename<<endl;
        return;
    }

    string eilute;
    getline(failas, eilute); //praleidziam pirma eilute (antrastes eilute)

    studentas laik;
    while(getline(failas, eilute)) //skaito kiekviena eil atskirai
    
    {
        istringstream ss(eilute); //naudojame string stream duom skaitymui is eilutes
        ss>>laik.Vard>>laik.Pav;

        int paz;
        laik.nd.clear(); //isvalom ankstesnius duom is vekt jei ju buvo

        vector<float> laikiniPaz; //laikinas vekt pazymiam saugoti
         while (ss>>paz) //nuskaitom visus sk is eilutes ir dedam i laikiniPaz
        {
            laikiniPaz.push_back(paz);
        }

        //Paskutinis nuskaitytas sk. yra egzamino pazymys
        if (!laikiniPaz.empty()) {
            laik.egz = laikiniPaz.back();
            laikiniPaz.pop_back();  //Pasaliname egzamina is ND saraso
        } 
        laik.nd=move(laikiniPaz); //perkeliamia visus pazymius i stud struktura
        grupe.push_back(laik); //pridedam studenta i studentu sarasa
    }
    failas.close();
}

void spausdintiRez(vector<studentas>& grupe, bool iFaila, char pasirinkimas, const string& failoPavadinimas)
{
    //pirma- apskaiciuoti galutinius balus
    for (auto& stud : grupe) 
    {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    //antra- sursiuoti studentus
    rusiuotiStud(grupe, 'g');
    
if (iFaila) //jei i faila
{
    vector<string> eilutes; //vektorius eilutems kaupti
    eilutes.reserve(grupe.size()); //rezervuojam vieta is anksto visiems studentams

    for(const auto& stud : grupe) //sukaupiam visus rezultatus i vektoriu (kad veliau vienu metu atspausdint)
    {
        ostringstream ss; //naudjam ostringstream kad surinktumevisus stud duom i eil
        ss<<setw(15)<<std::left<<stud.Vard<<setw(20)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
        eilutes.push_back(ss.str()); //irasom suformuota eil i vekt
    }
        
    ofstream failas(failoPavadinimas);
        if (!failas) {
            cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
            return;
        }

    for (const auto& eil : eilutes) //Rašome visas eilutes į failą vienu kartu (taip išvengiame lėto spausdinimo per `<<`)
    {
        failas.write(eil.c_str(), eil.size()); //Rašoma tiesiogiai iš `c_str()` į failą
    }
    failas.close();
    cout<<"Rezultatai issaugoti faile" << failoPavadinimas << "`.\n";
    }
else //jei i ekrana
{
    //optimizuotas isvedimas i ekrana
    ostringstream buffer;

    buffer<<setw(15)<<std::left<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<((pasirinkimas =='v') ? "Galutinis (Vid.)" : "Galutinis (Med.)")<<endl;
    buffer<<"--------------------------------------------------------------"<< endl;

    for (const auto& stud : grupe) //visi duom i bufferi, kad isvengt leto cout
    {
        buffer<<setw(15)<<std::left<<stud.Vard<<setw(15)<<stud.Pav<<setw(20)<<fixed<<setprecision(2)<<stud.Gal<< endl;
    }
    std::cout.write(buffer.str().c_str(), buffer.str().size()); //Galutinis `cout.write()`, kuris leidžia išvesti viską iš karto ir pagreitina procesą
}
}
