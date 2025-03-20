#include "studentas.h"

#ifndef SUFAILAIS_H
#define SUFAILAIS_H

template<typename Container, typename T>
void nuskaitymasFile(Container &grupe, const string& filename);

void spausdintiRez2( vector<studentas<vector<float>>> grupe, bool iFaila, char pasirinkimas, char rusiavimoPas);

template<typename Container>
void spausdintiRez(Container& grupe, bool iFaila, char pasirinkimas, const string& failoPavadinimas);



#endif