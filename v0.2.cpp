#include "1darboHeaderisVect.h"
#include "LaikoMatavimas.h"

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
    if (!failas) //patikrinam ar atsidare failas
    {
        cerr<<"nepavyko atidaryti failo!"<<filename<<endl;
        return;
    }

    string eilute;
    getline(failas, eilute); //praleidziam pirma eilute (antrastes eilute)

    studentas laik;
    while(getline(failas, eilute)) //skaito kiekviena eil atskirai
    
    {
        istringstream ss(eilute); //naudojame string stream duom skaitymui is eilutes
        ss>>laik.Vard>>laik.Pav;

        int paz;
        laik.nd.clear(); //isvalom ankstesnius duom is vekt jei ju buvo

        vector<float> laikiniPaz; //laikinas vekt pazymiam saugoti
         while (ss>>paz) //nuskaitom visus sk is eilutes ir dedam i laikiniPaz
        {
            laikiniPaz.push_back(paz);
        }

        //Paskutinis nuskaitytas sk. yra egzamino pazymys
        if (!laikiniPaz.empty()) {
            laik.egz = laikiniPaz.back();
            laikiniPaz.pop_back();  //Pasaliname egzamina is ND saraso
        } 
        laik.nd=move(laikiniPaz); //perkeliamia visus pazymius i stud struktura
        grupe.push_back(laik); //pridedam studenta i studentu sarasa
    }
    failas.close();
}

bool pagalVarda(const studentas& a, const studentas& b) { return a.Vard<b.Vard; }
bool pagalPavarde(const studentas& a, const studentas& b) { return a.Pav<b.Pav; }
bool pagalGal(const studentas& a, const studentas& b) { return a.Gal>b.Gal;}

void rusiuotiStud(vector<studentas>& grupe, char rusiavimoPas)
{
    if(rusiavimoPas=='v')
    {
        sort(grupe.begin(), grupe.end(), pagalVarda);
    }
    else if (rusiavimoPas=='p')
    {
        sort(grupe.begin(), grupe.end(), pagalPavarde);
    }
    else if (rusiavimoPas=='g')
    {
        sort(grupe.begin(), grupe.end(), pagalGal);
    }
}

void spausdintiRez( vector<studentas>& grupe, bool iFaila, char pasirinkimas, char rusiavimoPas)
{
    //pirma- apskaiciuoti galutinius balus
    for (auto& stud : grupe) 
    {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    //antra- sursiuoti studentus
    rusiuotiStud(grupe, rusiavimoPas);
    
if (iFaila) //jei i faila
{
    vector<string> eilutes; //vektorius eilutems kaupti
    eilutes.reserve(grupe.size()); //rezervuojam vieta is anksto visiems studentams

    for(const auto& stud : grupe) //sukaupiam visus rezultatus i vektoriu (kad veliau vienu metu atspausdint)
    {
        ostringstream ss; //naudjam ostringstream kad surinktumevisus stud duom i eil
        ss<<stud.Vard<<setw(20)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
        eilutes.push_back(ss.str()); //irasom suformuota eil i vekt
    }
        
    ofstream failas("rezultatai.txt" );
     if(!failas)
        {
            cerr<<"nepavyko sukurti failo rezultatams";
            return;
        }

    for (const auto& eil : eilutes) //Rašome visas eilutes į failą vienu kartu (taip išvengiame lėto spausdinimo per `<<`)
    {
        failas.write(eil.c_str(), eil.size()); //Rašoma tiesiogiai iš `c_str()` į failą
    }
    failas.close();
    cout<<"Rezultatai issaugoti faile `rezultatai.txt`.\n";
}
else //jei i ekrana
{
    //optimizuotas isvedimas i ekrana
    ostringstream buffer;

    buffer<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<((pasirinkimas =='v') ? "Galutinis (Vid.)" : "Galutinis (Med.)")<<endl;
    buffer<<"--------------------------------------------------------------"<< endl;

    for (const auto& stud : grupe) //visi duom i bufferi, kad isvengt leto cout
    {
        buffer<<stud.Vard<<setw(15)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
    }
    std::cout.write(buffer.str().c_str(), buffer.str().size()); //Galutinis `cout.write()`, kuris leidžia išvesti viską iš karto ir pagreitina procesą
}
}

int main() {
srand(time(0)); //pradinis seed nustatymas

vector<studentas> grupe;
char pasirinkimas;
char rusiavimoPas;
char isvedimoPasirinkimas;
int meniu;

LaikoMatavimas programa("Bendras programos vykdymas");
programa.pradeti();

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
        LaikoMatavimas failoNuskaitymas("Failo nuskaitymas");
        failoNuskaitymas.pradeti();
        nuskaitymasFile(grupe, "Studentai1000000.txt");
        failoNuskaitymas.baigti();
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
cout<<" [v] - vidurki\n [m] - mediana\n";
cin>>pasirinkimas;
while (pasirinkimas != 'v' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
        cin >> pasirinkimas;
}

cout<<"Pagal ka rusiuoti studentus?:\n [v] - varda\n [p] - pavarde\n [g] - galutini bala\n";
cin>>rusiavimoPas;

 cout<<"Kur vesti rezultatus?\n [e] - ekrane\n [f] - i faila\n ";
 cin>>isvedimoPasirinkimas;

 bool iFaila=(isvedimoPasirinkimas=='f'); //jei f -true, jei e-false

 LaikoMatavimas rezultatuIsvedimas("Rezultatu isvedimas");
rezultatuIsvedimas.pradeti();
 spausdintiRez(grupe, iFaila, pasirinkimas, rusiavimoPas);
rezultatuIsvedimas.baigti();
   
 programa.baigti(); 

 return 0;

/*for(auto a : grupe)
{
    cout<<a.Vard<<"  "<<a.Pav<<endl;
}*/
// g++ -o v0.2 "v0.2.cpp"
//./v0.2
//g++ -o v0.2 v0.2.cpp LaikoMatavimas.cpp


}
