#include "studentas.h"
#include "rikiavimas.h"
#include "sufailais.h"
#include "LaikoMatavimas.h"
#include "tyrimas3.h"


int main() {
    string aplankas= "test_files";
    string rezultataiAplankas= "rezultatai";
    string failas= aplankas + "/studentai_10000000.txt";

    //testuojame su vector
    cout<<"Testuojame vector...\n";
    testuotiKonteineri<vector<studentas<vector<float>>>>(failas, rezultataiAplankas);

    //testuojame su list
    cout<<"Testuojame list...\n";
    testuotiKonteineri<list<studentas<list<float>>>>(failas, rezultataiAplankas);

    //testuojame su deque
    cout<<"Testuojame deque...\n";
    testuotiKonteineri<deque<studentas<deque<float>>>>(failas, rezultataiAplankas);

    return 0;
}
