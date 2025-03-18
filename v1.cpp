##include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"
#include "tyrimas3.h"
#include "tyrimas4.h"
#include "tyrimas5.h"
#include "tyrimas6.h" 

void meniu() {
    cout<<"      PASIRINKITE TYRIMA      \n";
    cout<<" [1] - Tyrimas 3\n";
    cout<<" [2] - Tyrimas 4\n";
    cout<<" [3] - Tyrimas 5\n";
    cout<<" [4] - Tyrimas 6\n";
    cout<<" [0] - Baigti\n";
    cout<<" PASIRINKIMAS: ";
}

void pasirinktiFaila(string& failas){
    int pasirinkimas;
    cout<<" \n Pasirinkite testavimo FAILA: \n";
    cout << "[1] - 1000 studentų\n";
    cout << "[2] - 10 000 studentų\n";
    cout << "[3] - 100 000 studentų\n";
    cout << "[4] - 1 000 000 studentų\n";
    cout << "[5] - 10 000 000 studentų\n";
    cout<<" PASIRINKIMAS: ";

    cin>>pasirinkimas;

    switch (pasirinkimas) {
        case 1: failas= "test_files/studentai_1000.txt"; break;
        case 2: failas= "test_files/studentai_10000.txt"; break;
        case 3: failas= "test_files/studentai_100000.txt"; break;
        case 4: failas= "test_files/studentai_1000000.txt"; break;
        case 5: failas= "test_files/studentai_10000000.txt"; break;
        default:
            cout<<"NETEISINGAS pasirinkimas!! Naudojamas failas su 1000 studentu \n";
            failas= "test_files/studentai_1000.txt"; 
    }
}
int main() {
    string aplankas= "test_files";
    string rezultataiAplankas= "rezultatai";
    string failas;

    int pasirinkimas;
    do {
        meniu();
        cin>>pasirinkimas;
        if(pasirinkimas==1 || pasirinkimas==2 || pasirinkimas==3 || pasirinkimas==4){
            pasirinktiFaila(failas);
        }

        switch(pasirinkimas){
            case 1:
            cout << "Vykdomas Tyrimas 3...\n";
            testuotiKonteineri<vector<studentas<vector<float>>>>(failas, rezultataiAplankas);
            testuotiKonteineri<list<studentas<list<float>>>>(failas, rezultataiAplankas);
            testuotiKonteineri<deque<studentas<deque<float>>>>(failas, rezultataiAplankas);
            break;

            case 2:
            cout<<"Vykdomas Tyrimas 4...\n";
            testuotiSkaidymoStrategija<vector<studentas<vector<float>>>>(failas, rezultataiAplankas);
            testuotiSkaidymoStrategija<list<studentas<list<float>>>>(failas, rezultataiAplankas);
            testuotiSkaidymoStrategija<deque<studentas<deque<float>>>>(failas, rezultataiAplankas);
            break;

            case 3:
            cout<<"Vykdomas Tyrimas 5...\n";
            testuotiOptimizuotaSkaidyma<vector<studentas<vector<float>>>>(failas, rezultataiAplankas);
            testuotiOptimizuotaSkaidyma<list<studentas<list<float>>>>(failas, rezultataiAplankas);
            testuotiOptimizuotaSkaidyma<deque<studentas<deque<float>>>>(failas, rezultataiAplankas);
            break;

            case 4:
            cout<<"Vykdomas Tyrimas 6...\n";
            testuotiSkaidymoStrategija3<vector<studentas<vector<float>>>>(failas, rezultataiAplankas);
            break;

            case 0:
            cout<<"PROGRAA BAIGTA.\n";
            break;

            default:
            cout<<"NETEISINGAS PASIRINKIMAS!! Bandyti dar karta.\n";
        }
    } while (pasirinkimas!=0);

    return 0;
}

