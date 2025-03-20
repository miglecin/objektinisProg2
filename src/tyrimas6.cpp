#include <algorithm>
#include "studentas.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"
#include "sufailais.h"

// Šabloninė funkcija spausdinti kietiakus ir vargšus į failus
template <typename Container>
void spausdintiKietiakusIrVargsius(Container& vargsiai, Container& kietiakai, const string& vargsiuFailas, const string& kietiakuFailas) {
    
    // pagal galutinį balą
    char rusiavimoPas = 'g';
    rusiuotiStud(vargsiai, rusiavimoPas);
    rusiuotiStud(kietiakai, rusiavimoPas);

    ofstream vargsiaiFailasStream(vargsiuFailas);
    if (!vargsiaiFailasStream) {
        cerr << "Nepavyko sukurti failo: " << vargsiuFailas << endl;
        return;
    }
    for (const auto& stud : vargsiai) {
        vargsiaiFailasStream << stud.Vard << " " << stud.Pav << " " << stud.Gal << endl;
    }
    vargsiaiFailasStream.close();
    cout << "Vargšiai išsaugoti faile: " << vargsiuFailas << endl;

    // Spausdiname kietiakus
    ofstream kietiakaiFailasStream(kietiakuFailas);
    if (!kietiakaiFailasStream) {
        cerr << "Nepavyko sukurti failo: " << kietiakuFailas << endl;
        return;
    }
    for (const auto& stud : kietiakai) {
        kietiakaiFailasStream << stud.Vard << " " << stud.Pav << " " << stud.Gal << endl;
    }
    kietiakaiFailasStream.close();
    cout << "Kietiakai išsaugoti faile: " << kietiakuFailas << endl;
}

template <typename Container>
void testuotiSkaidymoStrategija3(const string& failoPavadinimas, const string& rezultataiAplankas) 
{
    Container grupe, vargsiai, kietiakai;
//tik jei konteineris yra vektorius
   if constexpr (std::is_same_v<Container, vector<studentas<vector<float>>>>) {
      
    string konteinerioTipas = "vector";

  string rezultatuFailas= rezultataiAplankas + "/optimizuotasSkaidymas3_" + konteinerioTipas + ".txt";

  try {
   //rez failo atidarymas
   ofstream rezultatai(rezultatuFailas, std::ios::app);
   if (!rezultatai) {
       throw std::runtime_error("Klaida: Nepavyko sukurti rezultatu failo: " + rezultatuFailas);
   }

   rezultatai<<"Testuojamas konteineris: "<<konteinerioTipas<<"\n";
   rezultatai<<"--------------------------------------------\n";

   //failo nuskaitymas
   LaikoMatavimas laikoMatavimasNuskaitymui("Failo nuskaitymas");
   laikoMatavimasNuskaitymui.pradeti();
   nuskaitymasFile(grupe, failoPavadinimas);
   laikoMatavimasNuskaitymui.baigti();
   rezultatai<< "---> Failo nuskaitymas uztruko: "<<laikoMatavimasNuskaitymui.gautiLaikoSkirtuma()<< " ms\n";

   //studentų rusiavimas
   LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
   laikoMatavimasRusiavimui.pradeti();
   rusiuotiStud(grupe, 'g');
   laikoMatavimasRusiavimui.baigti();
   rezultatai<< "---> Studentų rūšiavimas uztruko: "<<laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

   //skaidymas i dvi grupes
   LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes (optimizuotas)");
   laikoMatavimasSkaidymui.pradeti();
   isskirtiVargsusIrKietiakusOpt(grupe, vargsiai, kietiakai);
   laikoMatavimasSkaidymui.baigti();
   rezultatai<< "---> Studentų skaidymas į grupes (optimizuotas) uztruko: "<<laikoMatavimasSkaidymui.gautiLaikoSkirtuma()<< " ms\n";

    string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + konteinerioTipas + ".txt";
    string kietiakuFailas = rezultataiAplankas + "/kietiakai_" + konteinerioTipas + ".txt";
    spausdintiKietiakusIrVargsius(vargsiai, kietiakai, vargsiuFailas, kietiakuFailas);
   
   rezultatai<< "--------------------------------------------\n";
   rezultatai.close();

   cout<<"Rezultatai issaugoti faile: "<<rezultatuFailas<< "\n";
} catch (const std::exception& e) {
   cerr<<"Klaida: "<<e.what()<<endl;
}
}
}

//instanciacija, kad kompiliatorius zinotu ka kompiliuot
template void testuotiSkaidymoStrategija3<vector<studentas<vector<float>>>>(const string&, const string&);

template void spausdintiKietiakusIrVargsius<vector<studentas<vector<float>>>>(
     vector<studentas<vector<float>>>&, 
    vector<studentas<vector<float>>>&, 
    const string&, 
    const string&);