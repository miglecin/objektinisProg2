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
vector<studentas> grupe; //studentai su vektorium
char pasirinkimas;

cout<<"Koki metoda renkates gal. balui skaiciuoti?\n";
cout<<"Jei VIDURKI, rasykite [v], jei MEDIANA, rasykite [m]\n";
cin>>pasirinkimas;
while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
}
while(true) 
{
    studentas laik;
    cout<<"Studento vardas: ";
    cin>>laik.Vard;
    
    cout<<"Studento pavarde: ";
    cin>>laik.Pav;
    
    int nd_kiekis; 
    cout<<"Kiek nd pazymiu vesite?: ";
    while (true)
    {
        cin>>nd_kiekis;
        if(cin.fail() || nd_kiekis<=0 )
        {
            cout<<"Pazymiu kiekis turi buti teig. skaicius";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {break;};
    }
    
    laik.nd=new float[nd_kiekis]; //tikslus c masyvas
    
    cout<<"Iveskite "<<nd_kiekis<<" nd pazymius: " ;
    for (int i=0; i<nd_kiekis; i++)
    {
        while(true)
        {
            cin>>laik.nd[i];
            if(cin.fail() || laik.nd[i]<1 || laik.nd[i]>10) //jei ivedamas ne skaicius
                {
                    cout<<"Reikia ivesti pazymi nuo 1 iki 10: ";
                    cin.clear(); //isvaloma klaidos busena
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //pasaliname netinkama ivesti
                }
                else {break;}; //jei ivestis teisinga iseinama is ciklo
        }
    }  
    cout<<"Studento egzaminas (1-10): ";
    while (true)
    {
        cin>>laik.egz; 
        if(cin.fail() || laik.egz<1 || laik.egz>10 ) //jei ivedamas ne skaicius
        {
            cout<<"Reikia ivesti pazymi nuo 1 iki 10: ";
            cin.clear(); //isvaloma klaidos busena
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        else {break;}; //jei ivestis teisinga iseinama is ciklo
    }

    laik.nd_kiekis=nd_kiekis;
    laik.Gal= pasirinktasGal(laik.nd, laik.nd_kiekis, laik.egz, pasirinkimas);
    
    grupe.push_back(laik); //prideda studenta i vektoriu

    cout<<"Ar dar vesite kita studenta? (t/n): ";
    char ats;
    cin>>ats;
    if(ats=='n') break;

}
if(!grupe.empty()){
    if (pasirinkimas=='v')
    {
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<< "Galutinis (Vid.)"<<setw(15)<<endl;
    cout<<"--------------------------------------------"<<endl;
    }
    else 
    {
    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<< "Galutinis (Med.)"<<setw(15)<<endl;
    cout<<"--------------------------------------------"<<endl;
    }
  for (auto& a : grupe) 
 {
    cout<<a.Vard<<setw(15)<<a.Pav<<setw(20)<<fixed<<setprecision(2)<<a.Gal<<endl;
    delete[] a.nd; //atlaisvinami kiekvieno studento dinaminiai pazymiai
 }
}
else {cout<<"Nera studentu"<<endl;};

return 0;

}
