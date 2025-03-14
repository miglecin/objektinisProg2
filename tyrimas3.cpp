#include "tyrimas3.h"

void issaugotiRezultatus(const string& failoPavadinimas, const string& turinys) {
try{
    ofstream failas(failoPavadinimas, std::ios::app); //app-kad rez failas pasipildytu, o ne persirasytu
    if (!failas) {
        throw std::runtime_error("Klaida atidarant rezultatų failą: " + failoPavadinimas);
    }
    failas<< "\n--------------------------------------------------------\n";
    failas<<turinys<<endl;
    failas.close();
} catch (const std::exception& e) {
    cerr<<"Klaida: "<<e.what()<<endl;
}
}

template <typename Container>
void testuotiKonteineri(const string& failoPavadinimas, const string& rezultataiAplankas) {
    Container grupe;

   string konteinerioTipas;
    if constexpr (std::is_same_v<Container, vector<studentas<vector<float>>>>) {
        konteinerioTipas="vector";
    } else if constexpr (std::is_same_v<Container, list<studentas<list<float>>>>) {
        konteinerioTipas="list";
    } else if constexpr (std::is_same_v<Container, deque<studentas<deque<float>>>>) {
        konteinerioTipas="deque";
    }

    string rezultatuFailas=rezultataiAplankas + "/testavimas_" + konteinerioTipas + ".txt";
    try{
    ofstream rezultatai(rezultatuFailas, std::ios::app);
    if (!rezultatai) {
        throw std::runtime_error("Klaida: Nepavyko sukurti rezultatu failo: " + rezultatuFailas);
    }

    rezultatai<< "Testuojamas konteineris: "<<konteinerioTipas<< "\n";
    rezultatai<< "--------------------------------------------\n";

    //laiko matavimas - failo nuskaitymas
    LaikoMatavimas laikoMatavimasNuskaitymui("Failo nuskaitymas");
    laikoMatavimasNuskaitymui.pradeti();
    nuskaitymasFile(grupe, failoPavadinimas);
    laikoMatavimasNuskaitymui.baigti();
    rezultatai<< "---> Failo nuskaitymas uztruko: "<<laikoMatavimasNuskaitymui.gautiLaikoSkirtuma() << " ms\n";

    //laiko matavimas - rusiavimas
    LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
    laikoMatavimasRusiavimui.pradeti();
    rusiuotiStud(grupe, 'g');
    laikoMatavimasRusiavimui.baigti();
    rezultatai<< "---> Studentų rūšiavimas uztruko: "<<laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

    //laiko matavimas - skirstymas i dvi grupes
    Container vargsiai, kietiakai;
    LaikoMatavimas laikoMatavimasSkirstymui("Studentų skirstymas į grupes");
    laikoMatavimasSkirstymui.pradeti();
    isskirtiVargsusIrKietiakus(grupe, vargsiai, kietiakai);
    laikoMatavimasSkirstymui.baigti();
    rezultatai<< "---> Studentų skirstymas į grupes uztruko: "<<laikoMatavimasSkirstymui.gautiLaikoSkirtuma() << " ms\n";

    rezultatai<< "--------------------------------------------\n";
    rezultatai.close();

//ATLAISVINIMAS
grupe.clear();
if constexpr (std::is_same_v<Container, std::vector<studentas<typename Container::value_type>>>) {
    grupe.shrink_to_fit();
}
vargsiai.clear();
if constexpr (std::is_same_v<Container, std::vector<studentas<typename Container::value_type>>>) {
    vargsiai.shrink_to_fit();
}
kietiakai.clear();
if constexpr (std::is_same_v<Container, std::vector<studentas<typename Container::value_type>>>) {
    kietiakai.shrink_to_fit();
}


    cout<<"Rezultatai issaugoti faile: " <<rezultatuFailas<< "\n";
} catch (const std::exception& e) {
    cerr << "Klaida: "<<e.what()<<endl;
}
}

//aiski instanciacija butina, kai sablonu apibrezimai yra .cpp faile, kad linkeris juos rastu
template void testuotiKonteineri<std::vector<studentas<std::vector<float>>>>(const std::string&, const std::string&);
template void testuotiKonteineri<std::list<studentas<std::list<float>>>>(const std::string&, const std::string&);
template void testuotiKonteineri<std::deque<studentas<std::deque<float>>>>(const std::string&, const std::string&);
