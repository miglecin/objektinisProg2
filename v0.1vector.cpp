#include "1darboHeaderisVect.h"


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
do 
{
    cout<<"Studento vardas: ";
    cin>>laik.Vard;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"Studento pavarde: ";
    cin>>laik.Pav;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"Namu darbu pazymiai ";
    float paz;
        while(true)
        {
            cin>>paz;
            if (cin.peek()=='\n') break; //jei enter, ciklas stabdomas
            if(cin.fail()) break; //jei neteisingas inputas, stabdyti
            laik.nd.push_back(paz);
        }
    cout<<"Studento egzaminas : ";
    cin>>laik.egz; 

    laik.Gal= pasirinktasGal(laik.nd, laik.egz, pasirinkimas);
    grupe.push_back(laik);

    cout<<"Ar dar vesite kita studenta? (t/n): ";
    char ats;
    cin>>ats;
    if(ats=='n') break;

} while (true);
if (pasirinkimas=='v')
{
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(15)<< "Galutinis (Vid.)"<<setw(15)<<endl;
    cout<<"--------------------------------------------"<<endl;
}
else 
{
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(15)<< "Galutinis (Med.)"<<setw(15)<<endl;
    cout<<"--------------------------------------------"<<endl;
}
 for (auto a : grupe) 
 {
    cout<<a.Vard<<setw(15)<<a.Pav<<setw(20)<<fixed<<setprecision(2)<<a.Gal<<endl;
 }
/*for(auto a : grupe)
{
    cout<<a.Vard<<"  "<<a.Pav<<endl;
}*/

//g++ -o v0.1vector "v0.1vector.cpp"
//./v0.1vector
}
