#ifndef STRATEGIJA3_H
#define STRATEGIJA3_H

#include <vector>
#include "studentas.h"
#include "LaikoMatavimas.h"

// Spausdinti kietiakus ir vargšus į atskirus failus
void spausdintiKietiakusIrVargsius(
    std::vector<Studentas>& vargsiai, 
    std::vector<Studentas>& kietiakai, 
    const std::string& vargsiuFailas, 
    const std::string& kietiakuFailas);

// 3 strategija - Optimizuotas studentų skirstymas į vargšus ir kietiakus
void isskirtiVargsusIrKietiakusOpt(
    std::vector<Studentas>& grupe, 
    std::vector<Studentas>& vargsiai, 
    std::vector<Studentas>& kietiakai);

// Testavimo funkcija su laiko matavimais
void testuotiSkaidymoStrategija3(const std::string& failoPavadinimas, const std::string& rezultataiAplankas);

#endif // STRATEGIJA3_H
