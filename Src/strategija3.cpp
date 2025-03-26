#include <fstream>
#include "studentas.h"
#include "LaikoMatavimas.h"

// Spausdinti kietiakus ir vargšus į atskirus failus
template <typename T>
void spausdintiKietiakusIrVargsius(std::vector<Studentas<T>>& vargsiai, std::vector<Studentas<T>>& kietiakai, const std::string& vargsiuFailas, const std::string& kietiakuFailas) {
    // Pagal galutinį balą
    char rusiavimoPas = 'g';
    Studentas<T>::rusiuotiStud(vargsiai, rusiavimoPas);
    Studentas<T>::rusiuotiStud(kietiakai, rusiavimoPas);

    // Spausdiname vargšus
    std::ofstream vargsiaiFailasStream(vargsiuFailas);
    if (!vargsiaiFailasStream) {
        std::cerr << "Nepavyko sukurti failo: " << vargsiuFailas << std::endl;
        return;
    }
    for (const auto& stud : vargsiai) {
        vargsiaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
    }
    vargsiaiFailasStream.close();
    std::cout << "Vargšiai išsaugoti faile: " << vargsiuFailas << std::endl;

    // Spausdiname kietiakus
    std::ofstream kietiakaiFailasStream(kietiakuFailas);
    if (!kietiakaiFailasStream) {
        std::cerr << "Nepavyko sukurti failo: " << kietiakuFailas << std::endl;
        return;
    }
    for (const auto& stud : kietiakai) {
        kietiakaiFailasStream << stud.vardas() << " " << stud.pavarde() << " " << stud.galutinisBalsas() << std::endl;
    }
    kietiakaiFailasStream.close();
    std::cout << "Kietiakai išsaugoti faile: " << kietiakuFailas << std::endl;
}

// 3 strategija - Optimizuotas studentų skirstymas į vargšus ir kietiakus
template <typename T>
void isskirtiVargsusIrKietiakusOpt(std::vector<Studentas<T>>& grupe, std::vector<Studentas<T>>& vargsiai, std::vector<Studentas<T>>& kietiakai)  {
    if constexpr (std::is_same_v<T, std::vector<float>>) {
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

// Testavimo funkcija su laiko matavimais
template <typename T>
void testuotiSkaidymoStrategija3(const std::string& failoPavadinimas, const std::string& rezultataiAplankas) {
    vector<Studentas<T>> grupe, vargsiai, kietiakai;

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
            Studentas<T>::nuskaitymasFile(grupe, failoPavadinimas);
            laikoMatavimasNuskaitymui.baigti();
            rezultatai << "---> Failo nuskaitymas užtruko: " << laikoMatavimasNuskaitymui.gautiLaikoSkirtuma() << " ms\n";

            // Studentų rūšiavimas
            LaikoMatavimas laikoMatavimasRusiavimui("Studentų rūšiavimas");
            laikoMatavimasRusiavimui.pradeti();
            Studentas<T>::rusiuotiStud(grupe, 'g');
            laikoMatavimasRusiavimui.baigti();
            rezultatai << "---> Studentų rūšiavimas užtruko: " << laikoMatavimasRusiavimui.gautiLaikoSkirtuma() << " ms\n";

            // Skaidymas į dvi grupes (optimizuotas)
            LaikoMatavimas laikoMatavimasSkaidymui("Studentų skaidymas į grupes (optimizuotas)");
            laikoMatavimasSkaidymui.pradeti();
            isskirtiVargsusIrKietiakusOpt(grupe, vargsiai, kietiakai);
            laikoMatavimasSkaidymui.baigti();
            rezultatai << "---> Studentų skaidymas į grupes (optimizuotas) užtruko: " << laikoMatavimasSkaidymui.gautiLaikoSkirtuma() << " ms\n";

            std::string vargsiuFailas = rezultataiAplankas + "/vargsiai_" + typeid(T).name() + ".txt";
            std::string kietiakuFailas = rezultataiAplankas + "/kietiakai_" + typeid(T).name() + ".txt";
            spausdintiKietiakusIrVargsius(vargsiai, kietiakai, vargsiuFailas, kietiakuFailas);

            rezultatai << "--------------------------------------------\n";
            rezultatai.close();

            std::cout << "Rezultatai išsaugoti faile: " << rezultatuFailas << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Klaida: " << e.what() << std::endl;
        }
    }


// Instancijacija
template void testuotiSkaidymoStrategija3<std::vector<float>>(const std::string&, const std::string&);
template void testuotiSkaidymoStrategija3<std::list<float>>(const std::string&, const std::string&);
template void testuotiSkaidymoStrategija3<std::deque<float>>(const std::string&, const std::string&);

template void spausdintiKietiakusIrVargsius<std::vector<float>>(
    std::vector<Studentas<std::vector<float>>>&, 
    std::vector<Studentas<std::vector<float>>>&, 
    const std::string&, 
    const std::string&);

template void isskirtiVargsusIrKietiakusOpt<std::vector<float>>(
    std::vector<Studentas<std::vector<float>>>&, 
    std::vector<Studentas<std::vector<float>>>&, 
    std::vector<Studentas<std::vector<float>>>&);
    