#include "1darboHeaderis.h"


double generuotiGal( vector<float>&nd, int egz)
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

int main() {
studentas laik;
vector<studentas> grupe;
for(int i=0; i<2; i++)
{
    cout<<"Studento vardas: ";
    cin>>laik.Vard;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"Studento pavarde: ";
    cin>>laik.Pav;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"5 namu darbu pazymiai: ";
        for (int j=0; j<5; j++) {
            cin>>laik.nd[j];
        }
    cout<<"Studento egzaminas : ";
    cin>>laik.egz; 

    laik.Gal= generuotiGal(laik.nd, laik.egz);
    grupe.push_back(laik);
}

 cout<<setw(15)<<"Vardas"<<setw(15)<<"Pavarde"<<setw(10)<< "Galutinis"<<endl;
 cout<<"--------------------------------------------"<<endl;
 for (auto a : grupe) 
 {
    cout<<setw(15)<<a.Vard<<setw(15)<<a.Pav<<setw(20)<<fixed<<setprecision(2)<<a.Gal<<endl;
 }
/*for(auto a : grupe)
{
    cout<<a.Vard<<"  "<<a.Pav<<endl;
}*/


}