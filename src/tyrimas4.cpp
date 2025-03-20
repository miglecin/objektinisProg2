#include "tyrimas4.h"
#include "rikiavimas.h" 
#include "sufailais.h" 
#include "studentas.h" 

namespace fs = std::filesystem;

template <typename Container>
void spausdintiKietiakusIrVargsius(Container& kietiakai, Container& vargsiai, const string& failoPavadinimasKietiakai, const string& failoPavadinimasVargsiai, bool iFaila, char pasirinkimas)
{
    if (!fs::exists("results")) {
        fs::create_directory("results");
    }
    // Pirmiausia apskaičiuojame galutinius balus kietiakams ir vargšams
    for (auto& stud : kietiakai) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    for (auto& stud : vargsiai) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    // Rūšiuojame kietiakus ir vargšus pagal galutinį balą
    rusiuotiStud(kietiakai, 'g');
    rusiuotiStud(vargsiai, 'g');

    // Jei reikia išvesti į failą
    if (iFaila) {
        // Kietiakų rezultatai į failą
        vector<string> eilutesKietiakai;
        eilutesKietiakai.reserve(kietiakai.size());

        for (const auto& stud : kietiakai) {
            ostringstream ss;
            ss << setw(15) << std::left << stud.Vard 
               << setw(20) << stud.Pav 
               << setw(17) << fixed << setprecision(2) << stud.Gal << endl;
            eilutesKietiakai.push_back(ss.str());
        }

        ofstream failasKietiakai(failoPavadinimasKietiakai);
        if (!failasKietiakai) {
            cerr << "Nepavyko sukurti failo: " << failoPavadinimasKietiakai << endl;
            return;
        }
        for (const auto& eil : eilutesKietiakai) {
            failasKietiakai.write(eil.c_str(), eil.size());
        }
        failasKietiakai.close();

        // Vargsų rezultatai į failą
        vector<string> eilutesVargsiai;
        eilutesVargsiai.reserve(vargsiai.size());

        for (const auto& stud : vargsiai) {
            ostringstream ss;
            ss << setw(15) << std::left << stud.Vard 
               << setw(20) << stud.Pav 
               << setw(17) << fixed << setprecision(2) << stud.Gal << endl;
            eilutesVargsiai.push_back(ss.str());
        }

        ofstream failasVargsiai(failoPavadinimasVargsiai);
        if (!failasVargsiai) {
            cerr << "Nepavyko sukurti failo: " << failoPavadinimasVargsiai << endl;
            return;
        }
        for (const auto& eil : eilutesVargsiai) {
            failasVargsiai.write(eil.c_str(), eil.size());
        }
        failasVargsiai.close();

        cout << "Rezultatai issaugoti faile: " << failoPavadinimasKietiakai 
             << " ir " << failoPavadinimasVargsiai << ".\n";
    }
}

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

    if (!fs::exists(rezultataiAplankas)) {
        fs::create_directory(rezultataiAplankas);
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

        spausdintiKietiakusIrVargsius(kietiakai, vargsiai, "rezultatai/kietiakai.txt", "rezultatai/vargsiai.txt", true, 'v');

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

template void spausdintiKietiakusIrVargsius<std::vector<studentas<std::vector<float>>>>(
    std::vector<studentas<std::vector<float>>>& kietiakai, 
    std::vector<studentas<std::vector<float>>>& vargsiai,
    const std::string& failoPavadinimasKietiakai,
    const std::string& failoPavadinimasVargsiai,
    bool iFaila,
    char pasirinkimas);
    
template void spausdintiKietiakusIrVargsius<std::list<studentas<std::list<float>>>>(
    std::list<studentas<std::list<float>>>& kietiakai, 
    std::list<studentas<std::list<float>>>& vargsiai,
    const std::string& failoPavadinimasKietiakai,
    const std::string& failoPavadinimasVargsiai,
    bool iFaila,
    char pasirinkimas);

template void spausdintiKietiakusIrVargsius<std::deque<studentas<std::deque<float>>>>(
    std::deque<studentas<std::deque<float>>>& kietiakai, 
    std::deque<studentas<std::deque<float>>>& vargsiai,
    const std::string& failoPavadinimasKietiakai,
    const std::string& failoPavadinimasVargsiai,
    bool iFaila,
    char pasirinkimas);
