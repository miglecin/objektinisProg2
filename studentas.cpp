#include "studentas.h"
//std::stringstream buffer;

template <typename Container>
double generuotiGalvid(Container& nd, int egz) 
{
    double suma= 0;
    for (const auto& paz : nd) 
    {
        suma += paz;
    }
    double vidurkis=suma/ nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}

template <typename Container>
double generuotiGalmed(Container nd) 
{
    if constexpr (std::is_same_v<Container, list<float>>) 
    {
        // Jei konteineris yra LISTAS, naudojame .sort()
        nd.sort();
    } 
    else 
    {
        //jei konteineris yra VECTOR arba DEQUE, naudojame sort()
        sort(nd.begin(), nd.end());
    }
    size_t kiek=nd.size();
    auto it=nd.begin(); //pirmas elementas
    std::advance(it, kiek / 2); //perstumia per nurodyta sk elementu. Jis butina listui, nes jis neduoda random access ir neveiktu it+n

    if (kiek%2== 1) 
    {
        return *it;  // Jei nelyginis elementų kiekis, grazina ta sk
    } 
    else 
    {
        auto it2=it; //sukuria kopija it, kuris yra vidurinis elem
        std::advance(it2, -1); //perkialia 1 zingsniu atgal
        return (*it + *it2) / 2.0;  //Jei lyginis, grazina dvieju vid, * - kad gauti reiskmes o ne adresus
    }
}

//Funkcija pasirinktam galutiniam balui 
template <typename Container>
double pasirinktasGal(Container& nd, int egz, char kaip) 
{
    double Gal=0;
    if (kaip=='v') 
    {
        Gal=generuotiGalvid(nd, egz);
    } else if (kaip=='m') 
    {
        Gal=0.4 * generuotiGalmed(nd) + 0.6 * egz;
    }
    return Gal;
}

template <typename Container>
void randomPaz(Container& nd, int& egz, int kiek_nd) 
{
    nd.clear(); //pasalina senus duomenis
    for (int i= 0; i<kiek_nd; i++) 
    {
        nd.push_back(rand() % 10 + 1); //atsitiktiniai paz nuo 1 iki 10
    }
    egz=rand() % 10 + 1; //egz paz
}

void generuotiVardPav(string& vardas, string& pavarde) 
{
    static const char* vardai[] = {"Jonas", "Petras", "Mantas", "Dovydas", "Rokas"};
    static const char* pavardes[] = {"Kazlauskas", "Petraitis", "Jankauskas", "Masiulis", "Paulauskas"};

    int varduKiekis = sizeof(vardai) / sizeof(vardai[0]);
    int pavardziuKiekis = sizeof(pavardes) / sizeof(pavardes[0]);

    vardas=vardai[rand() % varduKiekis];
    pavarde=pavardes[rand() % pavardziuKiekis];
}




//EKSPLICITINĖS INSTANTIACIJOS
template double pasirinktasGal<std::vector<float>>(std::vector<float>&, int, char);
template double pasirinktasGal<std::list<float>>(std::list<float>&, int, char);
template double pasirinktasGal<std::deque<float>>(std::deque<float>&, int, char);

template void randomPaz<std::vector<float>>(std::vector<float>&, int&, int);
template void randomPaz<std::list<float>>(std::list<float>&, int&, int);
template void randomPaz<std::deque<float>>(std::deque<float>&, int&, int);