#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include "studentas.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"
#include "sufailais.h"

// 3 strategija - Optimizuotas studentų skirstymas į vargšus ir kietiakus
template <typename Container>
void isskirtiVargsusIrKietiakusOpt(Container& grupe, Container& vargsiai, Container& kietiakai) {
    if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
        // Pirmiausia paskaičiuojame visus galutinius balus
        for (auto& stud : grupe) {
            stud.galBalas(generuotiGalvid);  // Skaičiuojame galutinį balą pagal vidurkį
        }

        // Naudojame partition optimizuotam skirstymui
        auto it = std::partition(grupe.begin(), grupe.end(), [](const auto& stud) {
            return stud.galutinisBalsas() >= 5.0;
        });

        // Kietiakai lieka grupeje
        std::copy(grupe.begin(), it, std::back_inserter(kietiakai));
        // Vargsai perkelti į atskirą konteinerį
        std::copy(it, grupe.end(), std::back_inserter(vargsiai));

        // Pašaliname vargšus iš grupės
        grupe.erase(it, grupe.end());
    }
}

// 2. Testavimo funkcija su laiko matavimais
template <typename Container>
void testuotiSkaidymoStrategija3(const std::string& failoPavadinimas, const std::string& rezultataiAplankas) {
    Container grupe, vargsiai, kietiakai;

    if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
        std::string konteinerioTipas = "vector";

        std::string rezultatuFailas = rezultataiAplankas + "/optimizuotasSkaidymas3_" + konteinerioTipas + ".txt";

        try {
            // Rezultatų failo atidarymas
            std::ofstream rezultatai(rezultatuFailas, std::ios::app);
            if (!rezultatai) {
                throw std::runtime_error("Klaida: Nepavyko sukurti rezultatų failo: " + rezultatuFailas);
            }

            rezultatai << "Testuojamas konteineris: " << konteinerioTipas << "\n";
            rezultatai << "--------------------------------------------\n";

            // Failo nuskaitymas
            LaikoMatavimas laikoMatavimasNuskaitymui("Failo nuskaitymas");
            laikoMatavimasNuskaitymui.pradeti();
            nuskaitymasFile(grupe, failoPavadinimas);
            laikoMatavimasNuskaitymui.baigti();
            rezultatai << "---> Failo nuskaitymas užtruko: " << laikoMatavimasNuskaitymui.gautiLaikoSkirtuma() << " ms\n";

            // Studentų rūšiavimas
            LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
            laikoMatavimasRusiavimui.pradeti();
            rusiuotiStud(grupe, 'g');
            laikoMatavimasRusiavimui.baigti();
            rezultatai << "---> Studentų rūšiavimas užtruko: " << laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

            // Skaidymas į dvi grupes (optimizuotas)
            LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes (optimizuotas)");
            laikoMatavimasSkaidymui.pradeti();
            isskirtiVargsusIrKietiakusOpt(grupe, vargsiai, kietiakai);
            laikoMatavimasSkaidymui.baigti();
            rezultatai << "---> Studentų skaidymas į grupes (optimizuotas) užtruko: " << laikoMatavimasSkaidymui.gautiLaikoSkirtuma() << " ms\n";

            std::string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + konteinerioTipas + ".txt";
            std::string kietiakuFailas = rezultataiAplankas + "/kietiakai_" + konteinerioTipas + ".txt";
            spausdintiKietiakusIrVargsius(vargsiai, kietiakai, vargsiuFailas, kietiakuFailas);

            rezultatai << "--------------------------------------------\n";
            rezultatai.close();

            std::cout << "Rezultatai išsaugoti faile: " << rezultatuFailas << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Klaida: " << e.what() << std::endl;
        }
    }
}

// Instancijacija
template void testuotiSkaidymoStrategija3<std::vector<Studentas>>(const std::string&, const std::string&);
template void spausdintiKietiakusIrVargsius<std::vector<Studentas>>(
    std::vector<Studentas>&, 
    std::vector<Studentas>&, 
    const std::string&, 
    const std::string&);
