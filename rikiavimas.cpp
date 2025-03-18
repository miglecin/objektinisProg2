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

//1 strategija
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

//2 strategija
//SABLONINĖ FUNKCIJA STUDENTAMS ISSKAIDYTI I VIENA KONTEINERI (ISTRINANT IS BENDRO)
template <typename Container>
void isskirtiVargsus(Container& grupe, Container& vargsiai) {
    auto it=grupe.begin();
    while (it!=grupe.end()) 
    {
        if (it->Gal< 5.0) 
        {
            vargsiai.push_back(*it); //perkeliam i vargsu konteineri
            it=grupe.erase(it); //istrinam is bendro konteinerio
        } 
        else 
        {
            ++it;
        }
    }
}

//3 strategija
//SABLONINĖ FUNKCIJA STUDENTAMS GREITAI ISSKIRSTYTI NAUDOJANT OPT ALGORITMUS SU VEKT.
template <typename Container>
void isskirtiVargsusIrKietiakusOpt(Container& grupe, Container& vargsiai, Container& kietiakai) {
    if constexpr (std::is_same_v<Container, vector<typename Container::value_type>>) {
        //greitas stud skirstymas su partition tik vektoriams
        auto it= std::partition(grupe.begin(), grupe.end(), [](const auto& stud) 
        {
            return stud.Gal >= 5.0;
        });

        //kietiakai lieka grupeje
        std::copy(grupe.begin(), it, std::back_inserter(kietiakai));

        //vargsai perkelti i atskira konteineri
        std::copy(it, grupe.end(), std::back_inserter(vargsiai));

        //pasalinami vargsiai is grupes konteinerio
        grupe.erase(it, grupe.end());
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

template void isskirtiVargsus<std::vector<studentas<std::vector<float>>>>(
    std::vector<studentas<std::vector<float>>>&, 
    std::vector<studentas<std::vector<float>>>&);
    
template void isskirtiVargsus<std::list<studentas<std::list<float>>>>(
    std::list<studentas<std::list<float>>>&, 
    std::list<studentas<std::list<float>>>&);
    
template void isskirtiVargsus<std::deque<studentas<std::deque<float>>>>(
    std::deque<studentas<std::deque<float>>>&, 
    std::deque<studentas<std::deque<float>>>&);
    

template void isskirtiVargsusIrKietiakusOpt<std::vector<studentas<std::vector<float>>>>(
    std::vector<studentas<std::vector<float>>>&, 
    std::vector<studentas<std::vector<float>>>&, 
    std::vector<studentas<std::vector<float>>>&);
    

    
