#include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"

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
    try
    {
        nuskaitymasFile(grupe, "Studentai100000.txt");
    } 
    catch (const std::exception& e)
    {
        cerr << "Klaida nuskaitant failą: " << e.what() <<endl;
        continue;
    }

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

try
{
    LaikoMatavimas rezultatuIsvedimas("Rezultatu isvedimas");
    rezultatuIsvedimas.pradeti();
    spausdintiRez(grupe, iFaila, pasirinkimas, rusiavimoPas);
    rezultatuIsvedimas.baigti();
}
catch(const std::exception& e)
{
    cerr << "Klaida išvedant rezultatus: " << e.what() <<endl;
}
   
 programa.baigti(); 

 return 0;

//make clean
//make
//make run

}
