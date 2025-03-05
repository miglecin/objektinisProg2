#include "studentas.h"
#include "generuoti_failus.h"
#include "LaikoMatavimas.h"
#include "tyrimas1.h"

void testuotiFailoGeneravima(int skaicius, const std::string& aplankas) {
    LaikoMatavimas laikoMatavimas("Failo generavimas");
    laikoMatavimas.pradeti();

    generuotiFaila(skaicius, aplankas);  // Kviečiama funkcija, kuri generuoja failą

    laikoMatavimas.baigti();
}