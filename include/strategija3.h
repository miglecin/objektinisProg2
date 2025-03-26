#ifndef STRATEGIJA3_H
#define STRATEGIJA3_H

#include <vector>
#include "studentas.h"
#include "LaikoMatavimas.h"

// Spausdinti kietiakus ir vargšus į atskirus failus
template <typename Container>
void spausdintiKietiakusIrVargsius(Container& vargsiai, Container& kietiakai, const std::string& vargsiuFailas, const std::string& kietiakuFailas);

// 3 strategija - Optimizuotas studentų skirstymas į vargšus ir kietiakus
template <typename Container>
void isskirtiVargsusIrKietiakusOpt(Container& grupe, Container& vargsiai, Container& kietiakai);

// Testavimo funkcija su laiko matavimais
template <typename Container>
void testuotiSkaidymoStrategija3(const std::string& failoPavadinimas, const std::string& rezultataiAplankas);

#endif // STRATEGIJA3_H
