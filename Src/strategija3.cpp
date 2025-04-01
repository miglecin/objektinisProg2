#include "strategija3.h"

void spausdintiKietiakusIrVargsius(vector<Studentas>& vargsiai, vector<Studentas>& kietiakai, const string& vargsiuFailas, const string& kietiakuFailas) {
    char rusiavimoPas = 'g';
    Studentas::rusiuotiStud(vargsiai, rusiavimoPas);
    Studentas::rusiuotiStud(kietiakai, rusiavimoPas);

    ofstream vargsiaiFailasStream(vargsiuFailas);
    if (!vargsiaiFailasStream) {
        cerr << "Nepavyko sukurti failo: " << vargsiuFailas <<endl;
        return;
    }
    for (const auto& stud : vargsiai) {
        vargsiaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() <<endl;
    }
    vargsiaiFailasStream.close();

    ofstream kietiakaiFailasStream(kietiakuFailas);
    if (!kietiakaiFailasStream) {
        cerr << "Nepavyko sukurti failo: " << kietiakuFailas <<endl;
        return;
    }
    for (const auto& stud : kietiakai) {
        kietiakaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() <<endl;
    }
    kietiakaiFailasStream.close();
}

//3 strategija - Optimizuotas studentų skirstymas i vargsus ir kietiakus
void isskirtiVargsusIrKietiakusOpt(vector<Studentas>& grupe, vector<Studentas>& vargsiai, vector<Studentas>& kietiakai) {
    for (auto& stud : grupe) {
        float galutinis = stud.galBalas(generuotiGalvid);   // Skaičiuojame galutinį balą pagal vidurkį
    }

    auto it =std::partition(grupe.begin(), grupe.end(), [](const auto& stud) {
        return stud.galutinisBalsas() >= 5.0;
    });

    std::copy(grupe.begin(), it, std::back_inserter(kietiakai));
    std::copy(it, grupe.end(), std::back_inserter(vargsiai));

    grupe.erase(it, grupe.end());
}

//testavimo funkcija su laiko matavimais
void testuotiSkaidymoStrategija3(const string& failoPavadinimas, const string& rezultataiAplankas) {
    vector<Studentas> grupe, vargsiai, kietiakai;

    string konteinerioTipas = "vector";
    string rezultatuFailas = rezultataiAplankas + "/optimizuotasSkaidymas3_" + konteinerioTipas + ".txt";

    try {
        ofstream rezultatai(rezultatuFailas, std::ios::app);
        if (!rezultatai) {
            throw std::runtime_error("Klaida: Nepavyko sukurti rezultatų failo: " + rezultatuFailas);
        }

        rezultatai << "Testuojamas konteineris: " << konteinerioTipas << "\n";
        rezultatai << "--------------------------------------------\n";

        LaikoMatavimas laikoMatavimasNuskaitymui("Failo nuskaitymas");
        laikoMatavimasNuskaitymui.pradeti();
        Studentas::nuskaitymasFile(grupe, failoPavadinimas);
        laikoMatavimasNuskaitymui.baigti();
        rezultatai << "---> Failo nuskaitymas užtruko: " << laikoMatavimasNuskaitymui.gautiLaikoSkirtuma() << " ms\n";

        LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
        laikoMatavimasRusiavimui.pradeti();
        Studentas::rusiuotiStud(grupe, 'g');
        laikoMatavimasRusiavimui.baigti();
        rezultatai << "---> Studentų rūšiavimas užtruko: " << laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

        LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes (optimizuotas)");
        laikoMatavimasSkaidymui.pradeti();
        isskirtiVargsusIrKietiakusOpt(grupe, vargsiai, kietiakai);
        laikoMatavimasSkaidymui.baigti();
        rezultatai << "---> Studentų skaidymas į grupes (optimizuotas) užtruko: " << laikoMatavimasSkaidymui.gautiLaikoSkirtuma() << " ms\n";

        string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + typeid(Studentas).name() + ".txt";
        string kietiakuFailas = rezultataiAplankas + "/kietiakai_" + typeid(Studentas).name() + ".txt";
        spausdintiKietiakusIrVargsius(vargsiai, kietiakai, vargsiuFailas, kietiakuFailas);

        rezultatai << "--------------------------------------------\n";
        rezultatai.close();

        cout << "Rezultatai išsaugoti faile: " << rezultatuFailas << "\n";
    } catch (const std::exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    }
}
