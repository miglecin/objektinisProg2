#include "1darboHeaderisVect.h"


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

void nuskaitymasFile(vector<studentas>&grupe, const string& filename)
{
    ifstream failas(filename);
    if (!failas) 
    {
        cerr<<"nepavyko atidaryti failo!"<<filename<<endl;
        return;
    }

    string eilute;
    getline(failas, eilute); //praleidziam pirma eilute

    while (getline(failas, eilute))
    {
        stringstream ss(eilute);
        studentas laik;
        ss>>laik.Vard>>laik.Pav;

        int paz;
        laik.nd.clear();

         while (ss>>paz) {
            laik.nd.push_back(paz);
        }

        //Paskutinis nuskaitytas sk. yra egzamino pazymys
        if (!laik.nd.empty()) {
            laik.egz = laik.nd.back();
            laik.nd.pop_back();  //Pasaliname egzamina is ND saraso
        } else {
            cerr << "nera egamino pazymio eiluteje: " << eilute << endl;
            continue;
        }
        grupe.push_back(laik);
    }
    failas.close();
}

void spausdintiRez(const vector<studentas>& grupe, bool iFaila, char pasirinkimas)
{
    ofstream failoIsvedimas;
    if(iFaila)
    {
        failoIsvedimas.open("rezultatai.txt");
        if (!failoIsvedimas)
        {
            cerr<<"nepavyko sukurti failo rezultatams"<<endl;
            return;
        }
    }
    ostream& out= iFaila ? failoIsvedimas : cout;

    out<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<((pasirinkimas =='v') ? "Galutinis (Vid.)" : "Galutinis (Med.)")<<endl;
    out <<"--------------------------------------------------------------"<< endl;
     
    for (const auto& stud : grupe) {
        out<<stud.Vard<<setw(15)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
    }
    if (iFaila) 
    {
        cout<<"Rezultatai issaugoti faile `rezultatai.txt`.\n";
        failoIsvedimas.close();
    }
}
int main() {
srand(time(0)); //pradinis seed nustatymas

vector<studentas> grupe;
char pasirinkimas;
int meniu;

do
{
    studentas laik;
    int kiek_nd;

cout<<"Pasirinkite meniu veiksma: \n";
cout<<"1 - Ivesti ranka\n2 - Generuoti pazymius\n3 - Generuoti vardus, pavardes ir pazymius\n4 - Nuskaityti is failo\n5 - Baigti\n ";
cin>>meniu;

if (cin.fail() || meniu < 1 || meniu > 5) {
        cout << "Klaida! Pasirinkite skaičių nuo 1 iki 5.\n";
        cin.clear();  // Išvalome klaidos būseną
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Pašaliname blogą įvestį
        continue;  // Praleidžiame likusią ciklo iteraciją ir grįžtame prie meniu
    }

    if (meniu==5) break;

    if(meniu==4) 
    {
        nuskaitymasFile(grupe, "kursiokai.txt");
        continue;
    }

    if (meniu==1 || meniu==3 || meniu==2)
    {
        if(meniu==3) generuotiVardPav(laik.Vard, laik.Pav);
        else if(meniu==2 || meniu==1)
        {
            cout<<"Studento vardas: ";
            cin>>laik.Vard;
    
            cout<<"Studento pavarde: ";
            cin>>laik.Pav;
        }
    }
    if(meniu==2 || meniu==3)
    {
        cout<<"Kiek nd pazymiu generuoti? ";
        cin>>kiek_nd;
        randomPaz(laik.nd, laik.egz, kiek_nd);
    }
    else 
    {
        cout<<"Namu darbu pazymiai ";
        float paz;
    while (true) 
    {
        cin >> paz;

    if (cin.fail())  //Netinkamas input
    {   
        cout<< "Iveskite pazymi nuo 1 iki 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //isvaloma bloga ivestis
        continue; //tesiam cikla
    }
    if(paz<1 || paz>10)
    {
        cout<<"Iveskite pazymi nuo 1 iki 10: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue; //tesiam cikla
    }

    laik.nd.push_back(paz); //idedame i vektoriu
    if (cin.peek() == '\n') break; //kai enter, baigiama ivestis
    }
        
    cout<<"Studento egzaminas: ";
    while (true)
    {
        cin>>laik.egz;
        if(cin.fail() || laik.egz < 1 || laik.egz > 10) {
        cout << "Egzamino pazymys turi būti nuo 1 iki 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        }
    break;
    }
}
grupe.push_back(laik);

} while(true);

cout<<"Koki metoda renkates gal. balui skaiciuoti?\n";
cout<<"Jei VIDURKI, rasykite [v], jei MEDIANA, rasykite [m]\n";
cin>>pasirinkimas;
while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
}

for (auto& laik : grupe) {
    laik.Gal = pasirinktasGal(laik.nd, laik.egz, pasirinkimas);
}

 char isvedimoPasirinkimas;
 cout<<"Kur vesti rezultatus?\n [e] - ekrane\n [f] - i faila\n ";
 cin>>isvedimoPasirinkimas;

 bool iFaila=(isvedimoPasirinkimas=='f');
 spausdintiRez(grupe, iFaila, pasirinkimas);
 return 0;

/*for(auto a : grupe)
{
    cout<<a.Vard<<"  "<<a.Pav<<endl;
}*/
// g++ -o v0.2 "v0.2.cpp"
//./v0.2

}
