#ifndef TYRIMAS6_H
#define TYRIMAS6_H

#include "studentas.h"
#include "sufailais.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"

template <typename Container>
void spausdintiKietiakusIrVargsius(const Container& vargsiai, const Container& kietiakai, const string& vargsiuFailas, const string& kietiakuFailas);

template <typename Container>
void testuotiSkaidymoStrategija3(const string& failoPavadinimas, const string& rezultataiAplankas);

#endif // TYRIMAS6_H
