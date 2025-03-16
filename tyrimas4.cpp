#include "tyrimas4.h"
#include "rikiavimas.h" 

template <typename Container>
void testuotiSkaidymoStrategija(const string& failoPavadinimas, const string& rezultataiAplankas) {
    Container grupe, vargsiai, kietiakai;

    // Nustatome konteinerio tipa
    string konteinerioTipas;
    if constexpr (std::is_same_v<Container, vector<studentas<vector<float>>>>) {
        konteinerioTipas = "vector";
    } else if constexpr (std::is_same_v<Container, list<studentas<list<float>>>>) {
        konteinerioTipas = "list";
    } else if constexpr (std::is_same_v<Container, deque<studentas<deque<float>>>>) {
        konteinerioTipas = "deque";
    }

   string rezultatuFailas = rezultataiAplankas + "/skaidymas_" + konteinerioTipas + ".txt";

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

        //laiko matavimas - rusiavimas
        LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
        laikoMatavimasRusiavimui.pradeti();
        rusiuotiStud(grupe, 'g');
        laikoMatavimasRusiavimui.baigti();
        rezultatai<< "---> Studentų rūšiavimas uztruko: "<<laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

        //stud skaidyms i 2 grupes (kopijuojant)
        LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes");
        laikoMatavimasSkaidymui.pradeti();
        isskirtiVargsusIrKietiakus(grupe, vargsiai, kietiakai); 
        laikoMatavimasSkaidymui.baigti();
        rezultatai<< "---> Studentų skaidymas į grupes uztruko: "<<laikoMatavimasSkaidymui.gautiLaikoSkirtuma()<< " ms\n";

        rezultatai<< "--------------------------------------------\n";
        rezultatai.close();

        cout<<"Rezultatai issaugoti faile: "<<rezultatuFailas<< "\n";
    } catch (const std::exception& e) {
        cerr<<"Klaida: "<<e.what()<<endl;
    }
}

// Aiški instanciacija, kad kompiliatorius žinotų, ką kompiliuoti
template void testuotiSkaidymoStrategija<std::vector<studentas<std::vector<float>>>>(const std::string&, const std::string&);
template void testuotiSkaidymoStrategija<std::list<studentas<std::list<float>>>>(const std::string&, const std::string&);
template void testuotiSkaidymoStrategija<std::deque<studentas<std::deque<float>>>>(const std::string&, const std::string&);
