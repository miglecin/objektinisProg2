#include "studentas.h"

#ifndef SUFAILAIS_H
#define SUFAILAIS_H

template<typename Container, typename T>
void nuskaitymasFile(Container &grupe, const string& filename);

template<typename Container>
void spausdintiRez(Container& grupe, bool iFaila, char pasirinkimas, const string& failoPavadinimas);



#endif