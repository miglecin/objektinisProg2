#include "studentas.h"
#include "generuoti_failus.h"
#include "LaikoMatavimas.h"
#include "tyrimas1.h"

void testuotiFailoGeneravima(int skaiciuss, const string& aplankas)
 {
    LaikoMatavimas laikoMatavimas("Failo generavimas");
    laikoMatavimas.pradeti();

    generuotiFaila(skaiciuss, aplankas);  //Kvieciama funkcija, kuri generuoja faila

    laikoMatavimas.baigti();
}