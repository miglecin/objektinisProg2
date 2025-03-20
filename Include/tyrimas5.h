#ifndef TYRIMAS5_H
#define TYRIMAS5_H

#include "studentas.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"

// Sabloninės funkcijos deklaracijos
template <typename Container>
void spausdintiVargsius(Container& vargsiai, const string& failoPavadinimas);

template <typename Container>
void testuotiOptimizuotaSkaidyma(const string& failas, const string& rezultataiAplankas);


#endif // TYRIMAS5_H
