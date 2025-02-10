#include "1darboHeaderisMasyvas.h"


double generuotiGalvid( float* nd, int kiek, int egz)
{
    double suma=0;
    for (int i =0; i<kiek; i++) 
    {
        suma=suma+nd[i];
    }
    double vidurkis=suma/kiek;
    double Gal= 0.4 * vidurkis + 0.6 * egz;
    return Gal;
}

double generuotiGalmed(float* nd, int kiek)
{
    sort(nd, nd+kiek); //surikiuoja masyva

    if(kiek%2==1)
    {
        return nd[kiek/2]; //jei nelyginis, tada vidurine reiksme
    }
    else 
    {
        return( nd[kiek/2-1] + nd[kiek/2])/2.0; //jei lyginis, dvieju viduriniu vidurkis
    }
}

double pasirinktasGal(float* nd, int kiek, int egz, char kaip)
{
    double Gal=0;

    if( kaip=='v')
    {
        Gal=generuotiGalvid(nd,kiek,egz);
    }
    if( kaip=='m')
    {
        Gal= 0.4 * generuotiGalmed(nd,kiek) + 0.6 * egz;
    }
    return Gal;
}

int main() {
studentas* grupe=nullptr;
int studentu_kiekis=0;
char pasirinkimas;

cout<<"Koki metoda renkates gal. balui skaiciuoti?\n";
cout<<"Jei VIDURKI, rasykite [v], jei MEDIANA, rasykite [m]\n";
cin>>pasirinkimas;
while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
}
while (true) 
{
    studentas laik;
    cout<<"Studento vardas: ";
    cin>>laik.Vard;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"Studento pavarde: ";
    cin>>laik.Pav;
    cin.ignore();  // Išvalo buferį, jei po vardo liko \n
    cout<<"Namu darbu pazymiai ";
    float* laik_nd=new float[100]; //daug vietos
    int nd_kiekis=0;
    float paz;
        while(true)
        {
            if (cin.peek()=='\n') break; //jei enter, ciklas stabdomas
            cin>>paz;
            if(cin.fail()) break; //jei neteisingas inputas, stabdyti
            laik_nd[nd_kiekis++]=paz;
        }  
    cout<<"Studento egzaminas : ";
    cin>>laik.egz; 

    //Perkelti pažymius į tikslų dydį atitinkantį masyvą
    laik.nd = new float[nd_kiekis];
    for(int i=0; i<nd_kiekis; i++)
    {
        laik.nd[i]=laik_nd[i];
    }
    delete[] laik_nd; //atlaisvintas laikinas masyvas
    laik.nd_kiekis=nd_kiekis;

    laik.Gal= pasirinktasGal(laik.nd, laik.nd_kiekis, laik.egz, pasirinkimas);
    
    //pridedame nauja studenta i masyva
    studentas* temp = new studentas[studentu_kiekis+1];
        for (int i= 0; i<studentu_kiekis; i++) 
        {
            temp[i]=grupe[i];  //Nukopijuojame senus duomenis
        }
        temp[studentu_kiekis]=laik;  //Pridedame nauja studenta

        delete[] grupe;  //atlaisviname sena masyva
        grupe=temp;  //pakeiciame rodykle i nauja masyva
        studentu_kiekis++;

    cout<<"Ar dar vesite kita studenta? (t/n): ";
    char ats;
    cin>>ats;
    if(ats=='n') break;

}
if(studentu_kiekis>0)
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
 for (int i=0; i<studentu_kiekis; i++) 
 {
    cout<<grupe[i].Vard<<setw(15)<<grupe[i].Pav<<setw(20)<<fixed<<setprecision(2)<<grupe[i].Gal<<endl;
    delete[] grupe[i].nd; //atlaisviname dinamini masyva
 }
 delete[] grupe; //atlaisviname studentu masyva


}