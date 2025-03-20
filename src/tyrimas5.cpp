
#include "tyrimas5.h"
#include "studentas.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"

//sabloninė funkcija spausdinti vargšus į failą
template <typename Container>
void spausdintiVargsius( Container& vargsiai, const string& failoPavadinimas) {

     // pagal galutinį balą
     char rusiavimoPas = 'g';
     rusiuotiStud(vargsiai, rusiavimoPas);

    ofstream failas(failoPavadinimas);
    if (!failas) {
        cerr<< "Nepavyko sukurti failo: "<<failoPavadinimas << endl;
        return;
    }

    for (const auto& stud : vargsiai) {
        failas<< stud.Vard << " " << stud.Pav << " " << stud.Gal << endl;
    }

    failas.close();
    cout <<"Vargšiai išsaugoti faile: " <<failoPavadinimas<<endl;
}

//testuoja optimizuota skaidymo strategija
template <typename Container>
void testuotiOptimizuotaSkaidyma(const string& failoPavadinimas, const string& rezultataiAplankas) {
    Container grupe;
    Container vargsiai;

    //Nustatome konteinerio tipa
    string konteinerioTipas;
    if constexpr (std::is_same_v<Container, vector<studentas<vector<float>>>>) {
        konteinerioTipas = "vector";
    } else if constexpr (std::is_same_v<Container, list<studentas<list<float>>>>) {
        konteinerioTipas = "list";
    } else if constexpr (std::is_same_v<Container, deque<studentas<deque<float>>>>) {
        konteinerioTipas = "deque";
    }

   string rezultatuFailas = rezultataiAplankas + "/optimizuotasSkaidymas_" + konteinerioTipas + ".txt";

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
    char rusiavimoPas = 'g';
    rusiuotiStud(grupe, rusiavimoPas);
    laikoMatavimasRusiavimui.baigti();
    rezultatai<< "---> Studentų rūšiavimas uztruko: "<<laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

    //skaidymas i vargsiukus (pasalinant juos is bendro konteinerio)
    LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes (optimizuotas)");
    laikoMatavimasSkaidymui.pradeti();
    isskirtiVargsus(grupe, vargsiai);
    laikoMatavimasSkaidymui.baigti();
    rezultatai<< "---> Studentų skaidymas į grupes (optimizuotas) uztruko: "<<laikoMatavimasSkaidymui.gautiLaikoSkirtuma()<< " ms\n";

    string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + konteinerioTipas + ".txt";
    spausdintiVargsius(vargsiai, vargsiuFailas);

    rezultatai<< "--------------------------------------------\n";
    rezultatai.close();

    cout<<"Rezultatai issaugoti faile: "<<rezultatuFailas<< "\n";
} catch (const std::exception& e) {
    cerr<<"Klaida: "<<e.what()<<endl;
}
}

template void testuotiOptimizuotaSkaidyma<vector<studentas<vector<float>>>>(const string&, const string&);
template void testuotiOptimizuotaSkaidyma<list<studentas<list<float>>>>(const string&, const string&);
template void testuotiOptimizuotaSkaidyma<deque<studentas<deque<float>>>>(const string&, const string&);

template void spausdintiVargsius<std::vector<studentas<std::vector<float>>>>(
     std::vector<studentas<std::vector<float>>>&, 
    const std::string&);

template void spausdintiVargsius<std::list<studentas<std::list<float>>>>(
    std::list<studentas<std::list<float>>>&, 
    const std::string&);

template void spausdintiVargsius<std::deque<studentas<std::deque<float>>>>(
    std::deque<studentas<std::deque<float>>>&, 
    const std::string&);
