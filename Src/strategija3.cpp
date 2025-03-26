#include "strategija3.h"

// Spausdinti kietiakus ir vargšus į atskirus failus
void spausdintiKietiakusIrVargsius(std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakai, const std::string& vargsiuFailas, const std::string& kietiakuFailas) {
    char rusiavimoPas = 'g';
    Studentas::rusiuotiStud(vargsiai, rusiavimoPas);
    Studentas::rusiuotiStud(kietiakai, rusiavimoPas);

    std::ofstream vargsiaiFailasStream(vargsiuFailas);
    if (!vargsiaiFailasStream) {
        std::cerr << "Nepavyko sukurti failo: " << vargsiuFailas << std::endl;
        return;
    }
    for (const auto& stud : vargsiai) {
        vargsiaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
    }
    vargsiaiFailasStream.close();

    std::ofstream kietiakaiFailasStream(kietiakuFailas);
    if (!kietiakaiFailasStream) {
        std::cerr << "Nepavyko sukurti failo: " << kietiakuFailas << std::endl;
        return;
    }
    for (const auto& stud : kietiakai) {
        kietiakaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
    }
    kietiakaiFailasStream.close();
}

// 3 strategija - Optimizuotas studentų skirstymas į vargšus ir kietiakus
void isskirtiVargsusIrKietiakusOpt(std::vector<Studentas>& grupe, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakai) {
    for (auto& stud : grupe) {
        float galutinis = stud.galBalas(generuotiGalvid);   // Skaičiuojame galutinį balą pagal vidurkį
    }

    auto it = std::partition(grupe.begin(), grupe.end(), [](const auto& stud) {
        return stud.galutinisBalsas() >= 5.0;
    });

    std::copy(grupe.begin(), it, std::back_inserter(kietiakai));
    std::copy(it, grupe.end(), std::back_inserter(vargsiai));

    grupe.erase(it, grupe.end());
}

// Testavimo funkcija su laiko matavimais
void testuotiSkaidymoStrategija3(const std::string& failoPavadinimas, const std::string& rezultataiAplankas) {
    std::vector<Studentas> grupe, vargsiai, kietiakai;

    std::string konteinerioTipas = "vector";
    std::string rezultatuFailas = rezultataiAplankas + "/optimizuotasSkaidymas3_" + konteinerioTipas + ".txt";

    try {
        std::ofstream rezultatai(rezultatuFailas, std::ios::app);
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

        std::string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + typeid(Studentas).name() + ".txt";
        std::string kietiakuFailas = rezultataiAplankas + "/kietiakai_" + typeid(Studentas).name() + ".txt";
        spausdintiKietiakusIrVargsius(vargsiai, kietiakai, vargsiuFailas, kietiakuFailas);

        rezultatai << "--------------------------------------------\n";
        rezultatai.close();

        std::cout << "Rezultatai išsaugoti faile: " << rezultatuFailas << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }
}
