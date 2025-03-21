#include "tyrimas3.h"
#include "studentas.h"

namespace fs = std::filesystem;

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

    spausdintiKietiakusIrVargsius(kietiakai, vargsiai, rezultataiAplankas + "/kietiakai.txt", rezultataiAplankas + "/vargsiai.txt", true, 'v');

    rezultatai<< "--------------------------------------------\n";
    rezultatai.close();

    cout<<"Rezultatai issaugoti faile: " <<rezultatuFailas<< "\n";
} catch (const std::exception& e) {
    cerr << "Klaida: "<<e.what()<<endl;
}
}

//aiski instanciacija butina, kai sablonu apibrezimai yra .cpp faile, kad linkeris juos rastu
template void testuotiKonteineri<std::vector<studentas<std::vector<float>>>>(const std::string&, const std::string&);
template void testuotiKonteineri<std::list<studentas<std::list<float>>>>(const std::string&, const std::string&);
template void testuotiKonteineri<std::deque<studentas<std::deque<float>>>>(const std::string&, const std::string&);
