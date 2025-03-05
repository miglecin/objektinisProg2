#include "studentas.h"
//std::stringstream buffer;

double generuotiGalvid( vector<float>&nd, int egz)
{
    double suma=0;
    for (int i =0; i<nd.size(); i++) 
    {
        suma=suma+nd[i];
    }
    double vidurkis=suma/nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
    
}

double generuotiGalmed(vector<float>nd)
{
    sort(nd.begin(), nd.end()); //rikiuoja did tvarka

    int kiek= nd.size();
    if(kiek%2==1)
    {
        return nd[kiek/2]; //jei nelyginis, tada vidurine reiksme
    }
    else 
    {
        return( nd[kiek/2-1] + nd[kiek/2])/2.0; //jei lyginis, dvieju viduriniu vidurkis
    }
}

double pasirinktasGal(vector<float>&nd, int egz, char kaip)
{
    double Gal=0;

    if( kaip=='v')
    {
        Gal=generuotiGalvid(nd,egz);
    }
    if( kaip=='m')
    {
        Gal= 0.4 * generuotiGalmed(nd) + 0.6 * egz;
    }
    return Gal;
}

void randomPaz(vector<float>& nd, int& egz, int kiek_nd)
{
    nd.clear(); //pasalina senus vektorius
    for(int i=0; i<kiek_nd; i++)
    {
        nd.push_back(rand()%10+1); //paz nuo 1 iki 10
    }
    egz=rand()%10+1; //egzo balas
}

void generuotiVardPav(string& vardas, string& pavarde) 
{
    static const char* vardai[]= {"Jonas", "Petras", "Mantas", "Dovydas", "Rokas"};
    static const char* pavardes[]= {"Kazlauskas", "Petraitis", "Jankauskas", "Masiulis", "Paulauskas"};

    int varduKiekis=sizeof(vardai) / sizeof(vardai[0]);
    int pavardziuKiekis=sizeof(pavardes) / sizeof(pavardes[0]);

    vardas=vardai[rand()%varduKiekis];
    pavarde=pavardes[rand()%pavardziuKiekis];
}
