#include "1darboHeaderis.h"


double generuotiGalvid( vector<float>&nd, int egz)
{
    double suma=0;
    for (int i =0; i<nd.size(); i++) 
    {
        suma=suma+nd[i];
    }
    double vidurkis=suma/nd.size();
    double Gal= 0.4 * vidurkis + 0.6 * egz;
    return Gal;
}

double generuotiGalmed(vector<float>nd)
{
    sort(nd.begin(), nd.end()); //rikiuoja maz tvarka

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

int main() {
studentas laik;
vector<studentas> grupe;
char pasirinkimas;

cout<<"Koki metoda renkates gal. balui skaiciuoti?\n";
cout<<"Jei VIDURKI, rasykite [v], jei MEDIANA, rasykite [m]\n";
cin>>pasirinkimas;
while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
}
for(int i=0; i<2; i++)
{
    cout<<"Studento vardas: ";
    cin>>laik.Vard;
    
    cout<<"Studento pavarde: ";
    cin>>laik.Pav;
    
    cout<<"5 namu darbu pazymiai: ";
    laik.nd.resize(5); //vektorius turi penkias veitas, nebereikia strukturoje aprasyti
        for (int j=0; j<5; j++) {
            cin>>laik.nd[j];
        }
    cout<<"Studento egzaminas : ";
    cin>>laik.egz; 

    laik.Gal= pasirinktasGal(laik.nd, laik.egz, pasirinkimas);
    grupe.push_back(laik);
}
if (pasirinkimas=='v')
{
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<< "Galutinis (Vid.)"<<endl;
    cout<<"--------------------------------------------"<<endl;
}
else 
{
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<< "Galutinis (Med.)"<<endl;
    cout<<"--------------------------------------------"<<endl;
}
 for (auto a : grupe) 
 {
    cout<<a.Vard<<setw(15)<<a.Pav<<setw(15)<<fixed<<setprecision(2)<<a.Gal<<endl;
 }
/*for(auto a : grupe)
{
    cout<<a.Vard<<"  "<<a.Pav<<endl;
}*/


}
