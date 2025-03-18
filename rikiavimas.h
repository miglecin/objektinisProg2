#ifndef RIKIAVIMAS_H
#define RIKIAVIMAS_H

#include "studentas.h"

template <typename Container>
void rusiuotiStud(Container & grupe, char rusiavimoPas);

template <typename Container>
void isskirtiVargsusIrKietiakus(Container& grupe, Container& vargsiai, Container& kietiakai);

template <typename Container>
void isskirtiVargsus(Container& grupe, Container& vargsiai);

template <typename Container>
void isskirtiVargsusIrKietiakusOpt(Container& grupe, Container& vargsiai, Container& kietiakai);

#endif
