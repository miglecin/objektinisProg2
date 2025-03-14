#include "rikiavimas.h"
#include <algorithm>

//SABLONINĖ RUSIAVIMO FUNKCIJA
template <typename Container>
void rusiuotiStud(Container& grupe, char rusiavimoPas) {
    if constexpr (std::is_same_v<Container, list<typename Container::value_type>>) //kompiliavimo metu tikrina, ar konteineris yra listas
    { 
        //jei konteineris yra LIST, tada .sort() 
        if (rusiavimoPas=='v') {
            grupe.sort([](const auto& a, const auto& b) { return a.Vard < b.Vard; }); //[] – lambda capture list, tuščia, nes nereikia jokių kintamųjų iš išorės
        } else if (rusiavimoPas=='p') {
            grupe.sort([](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas=='g') {
            grupe.sort([](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    } 
    else 
    {
        //jei konteineris yra VECTOR arba DEQUE, tada sort
        if (rusiavimoPas=='v') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Vard < b.Vard; });
        } else if (rusiavimoPas=='p') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas=='g') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    }
}

//SABLONINĖ FUNKCIJA STUDENTAMS ISSKAIDYTI I VARGSUS IR KIETIAKUS
template <typename Container>
void isskirtiVargsusIrKietiakus(Container& grupe, Container& vargsiai, Container& kietiakai) {
    for (const auto& stud : grupe) {
        if (stud.Gal < 5.0) {
            vargsiai.push_back(stud);
        } else {
            kietiakai.push_back(stud);
        }
    }
}
//aiski instanciacija butina, kai sablonu apibrezimai yra .cpp faile, kad linkeris juos rastu
template void rusiuotiStud<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, char);
template void rusiuotiStud<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, char);
template void rusiuotiStud<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, char);

template void isskirtiVargsusIrKietiakus<std::vector<studentas<std::vector<float>>>>(
    std::vector<studentas<std::vector<float>>>&, 
    std::vector<studentas<std::vector<float>>>&, 
    std::vector<studentas<std::vector<float>>>&);

template void isskirtiVargsusIrKietiakus<std::list<studentas<std::list<float>>>>(
    std::list<studentas<std::list<float>>>&, 
    std::list<studentas<std::list<float>>>&, 
    std::list<studentas<std::list<float>>>&);

template void isskirtiVargsusIrKietiakus<std::deque<studentas<std::deque<float>>>>(
    std::deque<studentas<std::deque<float>>>&, 
    std::deque<studentas<std::deque<float>>>&, 
    std::deque<studentas<std::deque<float>>>&);

